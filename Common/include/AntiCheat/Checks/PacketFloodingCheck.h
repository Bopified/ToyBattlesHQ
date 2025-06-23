#ifndef PACKET_FLOODING_CHECK
#define PACKET_FLOODING_CHECK

#include "../Interfaces.h"
#include <unordered_map>
#include <deque>
#include <format>
#include "../../Utils/Utils.h"

namespace Ac
{
    class PacketFloodChecker : public IACChecker<PacketFloodingEvent>
    {
    private:
        struct PacketRecord
        {
            std::uint64_t serverTime;
            PacketFloodingEvent event;
        };

        std::unordered_map<uint32_t, std::deque<PacketRecord>> playerData;

        std::string floatToString(float value, int precision = 2)
        {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(precision) << value;
            return oss.str();
        }

    public:
        std::optional<ACFlag> processEvent(const PacketFloodingEvent& event) override
        {
            const std::uint64_t serverTime = Common::Utils::getCurrentTimestampMs();
            auto& records = playerData[event.session->getId()];
            records.push_back({ serverTime, event });

            while (!records.empty() && (serverTime - records.front().serverTime) > event.analysisWindowMs)
            {
                records.pop_front();
            }

            if (records.size() > event.maxPacketsPerSecond)
            {
                const ACFlag flag{ event.session->getId(), event.floodingType, "Packet flood: " + std::to_string(records.size()) +
                    " packets in " + floatToString((records.back().serverTime - records.front().serverTime) / 1000.0f) +
                    "s (max " + std::to_string(event.maxPacketsPerSecond) + ")" };
                records.clear();

                event.session->closeSocket();
                return flag;
            }

            return std::nullopt;
        }
    };
}

#endif