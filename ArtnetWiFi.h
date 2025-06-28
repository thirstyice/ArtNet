#pragma once
#ifndef ARTNET_WIFI_H
#define ARTNET_WIFI_H

#if defined(ESP_PLATFORM) || defined(ESP8266) || defined(ARDUINO_AVR_UNO_WIFI_REV2)                             \
    || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) || defined(ARDUINO_SAMD_MKR1000) \
    || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_RASPBERRY_PI_PICO_W) || defined(ARDUINO_UNOR4_WIFI)
#define ARTNET_ENABLE_WIFI
#endif

#ifdef ARTNET_ENABLE_WIFI
#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#if defined(ESP_PLATFORM) || defined(ARDUINO_ARCH_RP2040)
#include <WiFi.h>
#include <WiFiUdp.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#elif defined(ARDUINO_AVR_UNO_WIFI_REV2) || defined(ARDUINO_SAMD_MKRWIFI1010) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
    || defined(ARDUINO_SAMD_NANO_33_IOT)
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#elif defined(ARDUINO_SAMD_MKR1000)
#include <SPI.h>
#include <WiFi101.h>
#include <WiFiUdp.h>
#elif defined(ARDUINO_UNOR4_WIFI)
#include <WiFiS3.h>
#endif
#include "Artnet/Manager.h"

class ArtnetReceiverWiFi : public art_net::Receiver {
public:
    ArtnetReceiverWiFi() : Receiver(&udp) {
    }
protected:
    WiFiUDP udp;
    IPAddress localIP() override
    {
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040)
        if( WiFi.getMode() == WIFI_AP ) {
            return WiFi.softAPIP();
        } else {
            return WiFi.localIP();
        }
#else
        return WiFi.localIP();
#endif
    }
    IPAddress subnetMask() override
    {
#if defined(ARDUINO_ARCH_ESP32)
        if( WiFi.getMode() == WIFI_AP ) {
            return WiFi.softAPSubnetMask();
        } else {
            return WiFi.subnetMask();
        }
#else
        return WiFi.subnetMask();
#endif
    }
    void macAddress(uint8_t* mac) override
    {
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_RP2040)
        if( WiFi.getMode() == WIFI_AP ) {
            WiFi.softAPmacAddress(mac);
        } else {
            WiFi.macAddress(mac);
        }
#else
        WiFi.macAddress(mac);
#endif
    }
    inline bool isNetworkReady() override
    {
        auto status = WiFi.status();
        bool is_connected = status == WL_CONNECTED;
#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(ARDUINO_ARCH_RP2040)
        bool is_ap_active = WiFi.getMode() == WIFI_AP;
#else
        bool is_ap_active = status == WL_AP_CONNECTED;
#endif
        return is_connected || is_ap_active;
    }
};

class ArtnetSenderWiFi : public art_net::Sender {
public:
    ArtnetSenderWiFi() : Sender(&udp) {}
protected:
    WiFiUDP udp;
    inline bool isNetworkReady() override
    {
        auto status = WiFi.status();
        bool is_connected = status == WL_CONNECTED;
#if defined(ARDUINO_ARCH_ESP32) || defined(ESP8266) || defined(ARDUINO_ARCH_RP2040)
        bool is_ap_active = WiFi.getMode() == WIFI_AP;
#else
        bool is_ap_active = status == WL_AP_CONNECTED;
#endif
        return is_connected || is_ap_active;
    }
};

using ArtnetWiFi = art_net::Manager<WiFiUDP>;
using ArtnetWiFiSender = ArtnetSenderWiFi;
using ArtnetWiFiReceiver = ArtnetReceiverWiFi;
#endif  // ARTNET_ENABLE_WIFI

#endif  // ARTNET_WIFI_H
