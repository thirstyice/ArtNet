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

using Artnet = art_net::Manager<EthernetUDP>;
using ArtnetSender = art_net::Sender<EthernetUDP>;
using ArtnetReceiver = art_net::Receiver<EthernetUDP>;

#endif  // ARTNET_ETHER_H
