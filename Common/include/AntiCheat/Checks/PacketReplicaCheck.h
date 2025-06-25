#ifndef PACKET_REPLICATION_CHECK
#define PACKET_REPLICATION_CHECK

#include "../Interfaces.h"
#include <unordered_map>
#include <deque>
#include <format>
#include "../../Utils/Utils.h"

namespace Ac
{
    class PacketReplicationChecker : public IACChecker<PacketReplicationEvent>
    {
    private:
        // [SEID] -> [PacketHash] -> [timestamp]
        std::unordered_map<uint32_t, std::unordered_map<size_t, std::uint64_t>> playerData;
        static inline std::uint64_t analysisWindowMs = 300000;

        std::string floatToString(float value, int precision = 2)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(precision) << value;
            return oss.str();
        }

        size_t calculatePacketHash(const std::vector<std::uint8_t>& data)
        {
            std::size_t hash = 0;
            for (auto byte : data) 
            {
                hash ^= byte + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }

    public:
        std::optional<ACFlag> processEvent(const PacketReplicationEvent& event) override
        {
            const std::uint64_t serverTime = Common::Utils::getCurrentTimestampMs();
            const size_t packetHash = calculatePacketHash(event.data);
            auto& playerPackets = playerData[event.session->getId()];

            for (auto it = playerPackets.begin(); it != playerPackets.end(); ) 
            {
                if ((serverTime - it->second) > analysisWindowMs) it = playerPackets.erase(it);
                else ++it;
            }

            if (playerPackets.find(packetHash) != playerPackets.end())
            {
                const ACFlag flag{
                    event.session->getAccountId(),
                    "Packet Replication (e.g. WPE)",
                    "Packet replication detected (ID " + std::to_string(event.packetId) + "): " +
                    "Duplicate packet in " +
                    floatToString((serverTime - playerPackets[packetHash]) / 1000.0f) +
                    "s window"
                };

                playerPackets.clear();
                event.session->closeSocket();

                return flag;
            }

            playerPackets[packetHash] = serverTime;
            return std::nullopt;
        }
    };
}

#endif