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

template <class C>
class ArtnetEther : public C {
public:
    ArtnetEther() : C(&udp) {
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

using Artnet = ArtnetEther<art_net::Manager>;
using ArtnetSender = ArtnetEther<art_net::Sender>;
using ArtnetReceiver = ArtnetEther<art_net::Receiver>;

#endif  // ARTNET_ETHER_H
