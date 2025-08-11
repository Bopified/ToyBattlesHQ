#ifndef ROOMS_LIST_HANDLER_H
#define ROOMS_LIST_HANDLER_H

#include "../../Network/MainSession.h"
#include "Network/Packet.h"
#include "../../MainEnums.h"
#include "../../Classes/RoomsManager.h"
#include <memory>

namespace Main
{
	namespace Handlers
	{
        inline void handleRoomsList(const Common::Network::Packet& request, std::shared_ptr<Main::Network::Session> session,
            Main::Classes::RoomsManager& roomsManager)
        {
            const auto roomsList = roomsManager.getRoomsList();
            const auto size = roomsList.size();

            const std::size_t messageSize = size * sizeof(Main::Structures::SingleRoom) + sizeof(std::uint32_t);
            std::vector<std::uint8_t> message(messageSize);

            if (message.size() >= sizeof(std::uint16_t))
            {
                std::uint16_t size16 = static_cast<std::uint16_t>(size);
                std::memcpy(message.data(), &size16, sizeof(std::uint16_t));
                std::memcpy(message.data() + sizeof(std::uint16_t), &size16, sizeof(std::uint16_t));
            }

            const std::size_t roomsDataOffset = sizeof(std::uint32_t);
            const std::size_t roomsDataSize = size * sizeof(Main::Structures::SingleRoom);

            if (message.size() >= roomsDataOffset + roomsDataSize && !roomsList.empty())
            {
                std::memcpy(message.data() + roomsDataOffset, roomsList.data(), roomsDataSize);
            }

            Common::Network::Packet response;
            response.setTcpHeader(request.getSession(), Common::Enums::NO_ENCRYPTION);
            response.setCommand(request.getOrder(), 0, 37, 0);
            response.setData(message.data(), message.size());
            session->asyncWrite(response);
        }
	}	
}

#endif