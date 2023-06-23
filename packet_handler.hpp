#ifndef PACKET_HANDLER_HPP
#define PACKET_HANDLER_HPP

#include "packets.hpp"

class PacketHandlerInterface {
public:
    virtual ~PacketHandlerInterface() {}

    virtual void handleMotionPacket(const PacketData& packet) = 0;
    virtual void handleSessionPacket(const PacketData& packet) = 0;
    virtual void handleLapPacket(const PacketData& packet) = 0;
    virtual void handleEventPacket(const PacketData& packet) = 0;
    virtual void handleParticipantsPacket(const PacketData& packet) = 0;
    virtual void handleCarSetupPacket(const PacketData& packet) = 0;
    virtual void handleCarTelemetryPacket(const PacketData& packet) = 0;
    virtual void handleCarStatusPacket(const PacketData& packet) = 0;
    virtual void handleFinalClassificationPacket(const PacketData& packet) = 0;
    virtual void handleLobbyInfoPacket(const PacketData& packet) = 0;
    virtual void handleCarDamagePacket(const PacketData& packet) = 0;
    virtual void handleSessionHistoryPacket(const PacketData& packet) = 0;
};

#endif  // PACKET_HANDLER_HPP
