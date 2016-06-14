# azurewebsockets

This is a library which connects to the Microsoft Azure Cloud via websockets.
It was spun off from [streetlightd](https://github.com/bbvch/streetlightd)

# What

Using this library you may connect to the Microsoft Azure Cloud via AMQP over websockets. 
See examples/standaloneclient for a simple example application.


# Who

This library is authored by [bbv Software Services AG](https://www.bbv.ch).
Files in azure-uamqp-c were developed by Microsoft and fall under their copyright (MIT-License).

# How

Clone and build this repopsitory:

    git clone https://github.com/bbvch/azurewebsockets.git
    cd azurewebsockets
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    sudo make install


# License

This library is licensed under the LGPL-V3 license (where applicable, see LICENSE for further information).
