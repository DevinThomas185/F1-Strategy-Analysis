#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "udp_listener.hpp"
#include "packets.hpp"

#define BUFFER_SIZE 4096

UDPListener::UDPListener() {
    openSocket("192.168.0.109", "20779");
}

UDPListener::~UDPListener() {
    closeSocket();
}

void UDPListener::openSocket(std::string ipAddress, std::string port) {
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
    addr.sin_addr.s_addr = inet_addr(ipAddress.c_str()); // TODO: needs better error checking;
    addr.sin_port = ntohs(stoi(port)); // TODO: needs better error checking

    if (bind(socket_, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to bind UDP socket to port " << port << " at " << ipAddress << std::endl;
        close(socket_);
        exit(EXIT_FAILURE);
    }

    currentIPAddress = ipAddress;
    currentPort = port;
    std::cout << "Listening for UDP on " << ipAddress << ":" << port << std::endl;
}

void UDPListener::closeSocket() {
    if (socket_ != 0) {
        close(socket_);
        std::cout << "Stopped listening for UDP on " << currentIPAddress << ":" << currentPort << std::endl;
    }
}

void UDPListener::changeIPandPort(std::string newIP, std::string newPort) {
    closeSocket();
    openSocket(newIP, newPort);
}

PacketData UDPListener::getPacket() {
    char buffer[BUFFER_SIZE];

    // Receive UDP data into the buffer
    ssize_t bytesRead = 0;
    bytesRead = recv(socket_, buffer, BUFFER_SIZE, 0);
    if (bytesRead == -1) {
        std::cerr << "Failed to receive UDP data." << std::endl;
//        exit(EXIT_FAILURE); // TODO: Investigate if this is needed: changing port mid packet get will trigger here
    }

    // Convert the received data into a PacketData object
    PacketData packet;
    std::memcpy(&packet, buffer, sizeof(PacketData));

    return packet;
}


