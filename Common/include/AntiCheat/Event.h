#ifndef EVENT_AC_H
#define EVENT_AC_H

#include "DirectXPackedVector.h"
#include <string>
#include <memory>

namespace Ac
{
    struct ACEvent
    {
        virtual ~ACEvent() = default;
        enum class Type 
        { 
            PlayerPosition, 
            PlayerKill, 
            PacketFlooding,
            PacketReplication
        } type;
    };

    struct PacketFloodingEvent : ACEvent
    {
        std::shared_ptr<Common::Network::Session> session;
        std::size_t maxPacketsPerSecond;
        std::uint64_t analysisWindowMs;
        std::string floodingType;
        std::uint32_t packetId;

        PacketFloodingEvent(std::shared_ptr<Common::Network::Session> session_, std::size_t maxPacketsPerS_,
            std::uint64_t analysisWindowMs_, const std::string& type_, std::uint32_t packetId_)
            : session(session_), maxPacketsPerSecond(maxPacketsPerS_), analysisWindowMs(analysisWindowMs_),
            floodingType(type_), packetId(packetId_)
        {
            type = Type::PacketFlooding;
        }

        static constexpr Type typeValue = Type::PacketFlooding;
    };

    struct PacketReplicationEvent : ACEvent
    {
        std::shared_ptr<Common::Network::Session> session;
        std::uint16_t packetId;
        std::vector<std::uint8_t> data;

        PacketReplicationEvent(std::shared_ptr<Common::Network::Session> session_,  std::uint16_t packetId_, 
            const std::vector<std::uint8_t>& data_)
            : session(session_), packetId(packetId_), data(data_)
        {
            type = Type::PacketReplication;
        }

        static constexpr Type typeValue = Type::PacketReplication;
    };

    struct ACFlag
    {
        std::uint32_t sessionId;
        std::string cheatType;
        std::string details;
    };
}

#endif
