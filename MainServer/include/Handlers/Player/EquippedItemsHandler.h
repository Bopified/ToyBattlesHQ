#ifndef EQUIPPED_ITEMS_HANDLER
#define EQUIPPED_ITEMS_HANDLER

#include "../../Network/MainSession.h"
#include "Network/Packet.h"
#include "../../MainEnums.h"
#include "../../Structures/Item/MainBoughtItem.h"

namespace Main
{
	namespace Handlers
	{
		inline void handleEquippedItemSwitch(const Common::Network::Packet& request, std::shared_ptr<Main::Network::Session> session,
			Main::Classes::RoomsManager& roomsManager)
		{
			START_BENCHMARK

			if (request.getExtra() == 51) 
			{
				std::uint16_t character;
				std::uint32_t itemNumber;

				for (std::size_t idx = 0; idx < request.getOption(); ++idx)
				{
					std::memcpy(&character, request.getData() + idx * 12, sizeof(character));
					std::memcpy(&itemNumber, request.getData() + idx * 12 + 4, sizeof(itemNumber));
					session->switchItemEquip(character, itemNumber);
				}
			}
			else if (request.getMission() == 1)
			{ // Remove a single item based on the passed extra, which is the EquippedItem's type
				session->unequipItem(request.getExtra()); 
			}
			else if (request.getMission() == 0)
			{
				Main::Structures::ItemSerialInfo itemSerialInfo;
				std::uint64_t val = 0;
					
				for (std::size_t idx = 0; idx < request.getOption(); ++idx)
				{
					std::memcpy(&itemSerialInfo, request.getData() + idx * 8, sizeof(itemSerialInfo));
					std::memcpy(&val, request.getData() + idx * 8, sizeof(itemSerialInfo));
					if (val < static_cast<std::uint64_t>(Common::Constants::maxItemType))
					{ // val == equippedItem.type
						session->unequipItem(val); 
					}
					else
					{
						session->equipItem(itemSerialInfo.itemNumber);
					}
				}
			}

			Common::Network::Packet response;
			response.setTcpHeader(request.getSession(), Common::Enums::USER_LARGE_ENCRYPTION);
			response.setCommand(request.getOrder(), 0, request.getExtra(), request.getOption());
			session->asyncWrite(response);

			END_BENCHMARK(handleEquippedItemSwitch, session)
		}
	}
}

#endif