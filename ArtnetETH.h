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

// ETH.h is a library for Ethernet PHY, but we should use WiFi library's apis for sever/client
using Artnet = art_net::Manager<WiFiUDP>;
using ArtnetSender = art_net::Sender<WiFiUDP>;
using ArtnetReceiver = ArtnetReceiverETH;

#endif // ARTNET_ETH_H
