#ifndef PLAYER_STATE_HANDLER_H
#define PLAYER_STATE_HANDLER_H

#include "../../Network/MainSession.h"
#include "../../Network/MainSessionManager.h"
#include "Network/Packet.h"
#include <ConstantDatabase/Structures/SetItemInfo.h>
#include <Utils/Utils.h>
#include "../../Classes/Room.h"

#include "../../Detail/CdbUtils.h"

namespace Main
{
	namespace Handlers
	{
		inline void handlePlayerState(const Common::Network::Packet& request, std::shared_ptr<Main::Network::Session>session, Main::Classes::RoomsManager& roomsManager,
			const Main::Structures::CapsuleListDatabase& capsuleListDb)
		{
			START_BENCHMARK

			auto previousPlayerState = session->getPlayer().getPlayerState();
			const bool mustBroadcastItems = previousPlayerState == Common::Enums::STATE_INVENTORY || previousPlayerState == Common::Enums::STATE_SHOP 
				|| Common::Enums::STATE_CAPSULE;

			session->setPlayerState(static_cast<Common::Enums::PlayerState>(request.getOption()));	
			Common::Network::Packet response;
			response.setTcpHeader(request.getSession(), Common::Enums::NO_ENCRYPTION);

			if (static_cast<Common::Enums::PlayerState>(request.getOption()) == Common::Enums::PlayerState::STATE_CAPSULE)
			{ // capsule resends currency + eventual sales
				constexpr std::size_t chunkSize = 50;
				auto capsuleItems = CdbUtils::getCapsuleEvents(capsuleListDb.saleEventStartDate, capsuleListDb.saleEventEndDate, capsuleListDb.newMpPrice, 
					capsuleListDb.newRtPrice);
				std::size_t totalItems = capsuleItems.size();
				response.setOrder(83);

				for (std::size_t i = 0; i < totalItems; i += chunkSize)
				{
					session->sendCurrency();

					std::size_t currentChunkSize = std::min(chunkSize, totalItems - i);
					auto* chunkData = reinterpret_cast<std::uint8_t*>(&capsuleItems[i]);
					response.setData(chunkData, currentChunkSize * sizeof(Main::Structures::CapsuleList));
					response.setOption(currentChunkSize);
					session->asyncWrite(response);
				}
			}

			if (Main::Classes::Room* room = roomsManager.getRoomByNumber(session->getPlayer().getRoomNumber()))
			{
				const auto uniqueId = session->getAccountInfo().uniqueId;
				response.setCommand(Details::Orders::PLAYER_STATE_NOTIFICATION, 0, 0, static_cast<Common::Enums::PlayerState>(request.getOption()));
				response.setData(reinterpret_cast<const std::uint8_t*>(&uniqueId), sizeof(uniqueId));
				room->broadcastToRoom(response);
				room->setStateFor(uniqueId, static_cast<Common::Enums::PlayerState>(request.getOption()));
				
				if (mustBroadcastItems)
				{
					Details::broadcastPlayerItems(roomsManager, session, request);
				}
			}

			END_BENCHMARK(handlePlayerState, session)
		}
	}
}

#endif
