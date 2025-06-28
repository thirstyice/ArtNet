#pragma once
#ifndef ARTNET_ETHER_H
#define ARTNET_ETHER_H

#ifdef ARTNET_ETHER
    #error "Only one kind of ArtnetEther is supported at once!
#endif

#define ARTNET_ETHER

#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#ifdef ARTNET_NATIVE_ETHER
	#include <NativeEthernetUdp.h>
#else
	#include <EthernetUdp.h>
#endif
#include "Artnet/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
#include "Artnet/Manager.h"

template <class C>
class ArtnetOverEther : public C {
public:
    ArtnetOverEther() : C(&udp) {
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

using ArtnetEther = ArtnetOverEther<ArtnetParent>;
using ArtnetEtherSender = ArtnetOverEther<ArtnetSenderParent>;
using ArtnetEtherReceiver = ArtnetOverEther<ArtnetReceiverParent>

#ifndef ARTNET_DEFAULT_INTERFACE
#define ARTNET_DEFAULT_INTERFACE ARTNET_ETHER

using Artnet = ArtnetEther;
using ArtnetSender = ArtnetEtherSender;
using ArtnetReceiver = ArtnetEtherReceiver;

#endif // ARTNET_DEFAULT_INTERFACE

#endif  // ARTNET_ETHER_H
