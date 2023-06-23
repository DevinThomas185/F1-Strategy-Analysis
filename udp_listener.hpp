#ifndef UDP_LISTENER_HPP
#define UDP_LISTENER_HPP

#include "packets.hpp"

class UDPListener {
public:
    UDPListener();
    ~UDPListener();

    PacketData getPacket();
private:
    int socket_;
};

#endif  // UDP_LISTENER_HPP
