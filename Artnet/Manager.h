#pragma once
#ifndef ARTNET_MANAGER_H

#include "Common.h"
#include "Receiver.h"
#include "Sender.h"

class ArtnetParent : public art_net::Sender_, public art_net::Receiver_
{
    UDP* stream;

public:
    ArtnetParent(UDP* s) : Sender_(s), Receiver_(s), stream(s) {}
    void begin(uint16_t recv_port = art_net::DEFAULT_PORT)
    {
        this->stream->begin(recv_port);
    }
};

#endif // ARTNET_MANAGER_H
