#pragma once
#ifndef ARTNET_ETHER_H
#define ARTNET_ETHER_H

#define ARTNET_ENABLE_ETHER

#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#ifdef ARTNET_NATIVE_ETHER_H
	#include <NativeEthernetUdp.h>
#else
	#include <EthernetUdp.h>
#endif
#include "Artnet/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
#include "Artnet/Manager.h"

class ArtnetReceiverEther : public art_net::Receiver {
public:
    ArtnetReceiverEther() : Receiver(&udp) {
    }
protected:
    EthernetUDP udp;
    IPAddress localIP() override
    {
        return Ethernet.localIP();
    }
    IPAddress subnetMask() override
    {
        return Ethernet.subnetMask();
    }
    inline void macAddress(uint8_t* mac) override
    {
        Ethernet.MACAddress(mac);
    }
    bool isNetworkReady() override
    {
        return true;
    }
};

class ArtnetSenderEther : public art_net::Sender {
public:
    ArtnetSenderEther() : Sender(&udp) {}
protected:
    WiFEthernetUDP udp;
    bool isNetworkReady() override
    {
        return true;
    }
};

class ArtnetManagerEther : public art_net::Manager {
public:
    ArtnetManagerEther() : Manager(&udp) {
    }
protected:
    EthernetUDP udp;
    IPAddress localIP() override
    {
        return Ethernet.localIP();
    }
    IPAddress subnetMask() override
    {
        return Ethernet.subnetMask();
    }
    inline void macAddress(uint8_t* mac) override
    {
        Ethernet.MACAddress(mac);
    }
    bool isNetworkReady() override
    {
        return true;
    }
};

using Artnet = ArtnetManagerEther;
using ArtnetSender = ArtnetSenderEther;
using ArtnetReceiver = ArtnetReceiverEther;

#endif  // ARTNET_ETHER_H
