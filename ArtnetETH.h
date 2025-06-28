#pragma once
#ifndef ARTNET_ETH_H
#define ARTNET_ETH_H

#define ARTNET_ETH

#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#include <ETH.h>
#include <WiFiUdp.h>
#include "Artnet/Manager.h"

// ETH.h is a library for Ethernet PHY, but we should use WiFi library's apis for sever/client

template <class C>
class ArtnetOverETH : public C {
public:
    ArtnetOverETH() : C(&udp) {
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

using ArtnetETH = ArtnetOverETH<ArtnetParent>;
using ArtnetETHSender = ArtnetOverETH<ArtnetSenderParent>;
using ArtnetETHReceiver = ArtnetOverETH<ArtnetReceiverParent>;

#ifndef ARTNET_DEFAULT_INTERFACE
#define ARTNET_DEFAULT_INTERFACE ARTNET_ETH

using Artnet = ArtnetETH;
using ArtnetSender = ArtnetETHSender;
using ArtnetReceiver = ArtnetETHReceiver;

#endif // ARTNET_DEFAULT_INTERFACE

#endif // ARTNET_ETH_H
