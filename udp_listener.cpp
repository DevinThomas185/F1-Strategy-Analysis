#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "udp_listener.hpp"
#include "packets.hpp"

#define PORT 20779 // TODO: MAKE NOT HARD CODED
#define BUFFER_SIZE 4096
#define IP_ADDRESS "192.168.0.109" // TODO: MAKE NOT HARD CODED

UDPListener::UDPListener() {
    // Create UDP socket
    socket_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_ < 0) {
        std::cerr << "Failed to create UDP socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const void *)&optval, sizeof(int));

    // Bind the socket to the specified port
    struct sockaddr_in addr;
    bzero((char *)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP_ADDRESS); // ;
    addr.sin_port = ntohs(PORT);

    if (bind(socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to bind UDP socket to port " << PORT << "." << std::endl;
        close(socket_);
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening for UDP on " << PORT << std::endl;
}

UDPListener::~UDPListener() {
    close(socket_);
    std::cout << "Stopped listening for UDP on port " << PORT << std::endl;
}

PacketData UDPListener::getPacket() {
    char buffer[BUFFER_SIZE];

    // Receive UDP data into the buffer
    ssize_t bytesRead = 0;
    bytesRead = recv(socket_, buffer, BUFFER_SIZE, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive UDP data." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Convert the received data into a PacketData object
    PacketData packet;
    std::memcpy(&packet, buffer, sizeof(PacketData));

    return packet;
}


