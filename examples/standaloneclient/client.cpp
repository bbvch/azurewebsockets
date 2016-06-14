/*
 * (C) Copyright 2016
 * Simon Egli & Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+ or LGPL-3.0+
 */

#include <protocolstack/session/Session.h>
#include <protocolstack/session/Factory.h>

#include <csignal>
#include <memory>
#include <iostream>
#include <set>
#include <vector>
#include <string>

class Configuration :
        public session::Configuration
{
public:
    std::string message{};

    operator bool() const
    {
        return message != "";
    }
};

static Configuration parseCommandline(const std::vector<std::string> &arg)
{
    if (arg.size() != 5) {
        std::cout << "usage: standalonesession <host> <user> <password> <message>" << std::endl;
        return {};
    }

    Configuration configuration;
    configuration.host = arg[1];
    configuration.user = arg[2];
    configuration.password = arg[3];
    configuration.message = arg[4];
    std::cout << "Returning configuration...\n";
    return configuration;
}

static void waitForTermination()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGTSTP);

    if (sigprocmask(SIG_BLOCK, &mask, nullptr) < 0) {
        perror("sigprocmask");
        return;
    }

    if (sigwaitinfo(&mask, nullptr) < 0) {
        perror("wait for exit");
    }
}

static void receiver(const std::string& message)
{
    std::cout << "received message: " << message << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "start...\n";
    const std::vector<std::string> arg{argv, argv+argc};
    std::cout << "vector done...\n";
    const Configuration configuration = parseCommandline(arg);

    if (!configuration) {
        std::cout << "could not read configuration...\n";
        return -1;
    }
    //std::cout << "parsed commandline...\n";


    std::unique_ptr<Session> session{session::produce()};
    if(!session)
        throw std::runtime_error("Was not able to create session");
    //std::cout << "Created session...\n";
    session->setMessageCallback(receiver);
    //std::cout << "Have set Message Callback...\n";
    session->setConfiguration(configuration);
    //std::cout << "connecting to: " << configuration.host << std::endl;
    session->connect();
    //std::cout << "connected...\n";

    std::cout << "send message: " << configuration.message << std::endl;
    session->send(configuration.message);

    std::cout << "receive messages" << std::endl;
    waitForTermination();

    std::cout << "closing" << std::endl;
    session->close();

    return 0;
}
