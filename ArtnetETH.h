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

class ArtnetReceiverETH : public art_net::Receiver {
public:
    ArtnetReceiverETH() : Receiver(&udp) {
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

class ArtnetSenderETH : public art_net::Sender {
public:
    ArtnetSenderETH() : Sender(&udp) {}
protected:
    WiFiUDP udp;
    bool isNetworkReady() override
    {
        return true;
    }
};

class ArtnetManagerETH : public art_net::Manager {
public:
    ArtnetManagerETH() : Manager(&udp) {}
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

using Artnet = ArtnetManagerETH;
using ArtnetSender = ArtnetSenderETH;
using ArtnetReceiver = ArtnetReceiverETH;

#endif // ARTNET_ETH_H
