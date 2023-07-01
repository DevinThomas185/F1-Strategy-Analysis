#ifndef UDP_LISTENER_HPP
#define UDP_LISTENER_HPP

#include <string>
#include "packets.hpp"

class UDPListener {
public:
    UDPListener();
    ~UDPListener();

    PacketData getPacket();

    void openSocket(std::string ipAddress, std::string port);
    void closeSocket();
    void changeIPandPort(std::string newIP, std::string newPort);

private:
    int socket_;
    std::string currentIPAddress;
    std::string currentPort;
};

#endif  // UDP_LISTENER_HPP
