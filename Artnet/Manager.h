#pragma once
#ifndef ARTNET_MANAGER_H

#include "Common.h"
#include "Receiver.h"
#include "Sender.h"

namespace art_net {

class Manager : public Sender_<S>, Receiver_
{
    UDP* stream;

public:
    Manager(UDP* s) : Receiver_(s), stream(s) {}
    void begin(uint16_t recv_port = DEFAULT_PORT)
    {
        this->stream->begin(recv_port);
        this->Sender_<S>::attach(this->stream);
    }
};


} // namespace art_net

#endif // ARTNET_MANAGER_H
