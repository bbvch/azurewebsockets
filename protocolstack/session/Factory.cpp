/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include <protocolstack/session/Factory.h>

#include "AzureAmqpWs.h"


namespace session
{

Factory<Session*> factory()
{
  Factory<Session*> factory;
  //factory.add("none", []{return new session::Null();});
  //factory.add("azure-amqp", []{return new AzureAmqp();});
  factory.add("session", []{return new AzureAmqpWs();});
  //factory.add("azure-http", []{return new AzureHttp();});
  //factory.add("azure-mqtt", []{return new AzureMqtt();});
  //factory.add("simple-mqtt", []{return new SimpleMqtt();});
  return factory;
}

}
