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
            PacketFlooding 
        } type;
    };

    struct Position
    {
        DirectX::PackedVector::HALF positionX{};
        DirectX::PackedVector::HALF positionY{};
        DirectX::PackedVector::HALF positionZ{};

        Position(DirectX::PackedVector::HALF x, DirectX::PackedVector::HALF y, DirectX::PackedVector::HALF z)
            : positionX{ x }, positionY{ y }, positionZ{ z }
        {
        }
    };

    struct PacketFloodingEvent : ACEvent
    {
        std::shared_ptr<Common::Network::Session> session;
        std::uint64_t timestamp;
        std::size_t maxPacketsPerSecond;
        std::uint64_t analysisWindowMs;
        std::string floodingType;
        std::uint32_t packetId;

        PacketFloodingEvent(std::shared_ptr<Common::Network::Session> session_, std::uint64_t timestamp_, std::size_t maxPacketsPerS_,
            std::uint64_t analysisWindowMs_, const std::string& type_, std::uint32_t packetId_)
            : session(session_), timestamp(timestamp_), maxPacketsPerSecond(maxPacketsPerS_), analysisWindowMs(analysisWindowMs_),
            floodingType(type_), packetId(packetId_)
        {
            type = Type::PacketFlooding;
        }

        static constexpr Type typeValue = Type::PacketFlooding;
    };

    struct PlayerPositionEvent : ACEvent
    {
        std::shared_ptr<Common::Network::Session> session;
        std::uint64_t timestamp;
        Position position;

        PlayerPositionEvent(std::shared_ptr<Common::Network::Session> session_, std::uint64_t timestamp_, const Position& position_)
            : session(session_), timestamp(timestamp_), position(position_)
        {
            type = Type::PlayerPosition;
        }

        static constexpr Type typeValue = Type::PlayerPosition;
    };

   
    struct ACFlag
    {
        std::uint32_t sessionId;
        std::string cheatType;
        std::string details;
    };
}

#endif
