#pragma once
#ifndef ARTNET_ETH_H
#define ARTNET_ETH_H

#define ARTNET_ENABLE_ETH

#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#include <ETH.h>
#include <WiFiUdp.h>
#include "Artnet/Manager.h"

// ETH.h is a library for Ethernet PHY, but we should use WiFi library's apis for sever/client

template <class C>
class ArtnetETH : public C {
public:
    ArtnetETH() : C(&udp) {
    }
protected:
	WiFiUDP udp;
    IPAddress localIP() override
    {
        return ETH.localIP();
    }
    IPAddress subnetMask() override
    {
        return ETH.subnetMask();
    }
    void macAddress(uint8_t* mac) override
    {
        ETH.macAddress(mac);
    }
    bool isNetworkReady() override
    {
        return true;
    }
};

using Artnet = ArtnetETH<art_net::Manager>;
using ArtnetSender = ArtnetETH<art_net::Sender>;
using ArtnetReceiver = ArtnetETH<art_net::Receiver>;

#endif // ARTNET_ETH_H
