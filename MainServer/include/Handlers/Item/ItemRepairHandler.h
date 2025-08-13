#ifndef REPAIR_ITEM_HANDLER_H
#define REPAIR_ITEM_HANDLER_H

#include "../../Network/MainSession.h"
#include "../../../include/Structures/AccountInfo/MainAccountInfo.h"
#include "Network/Packet.h"
#include "../../Detail/Utilities.h"

namespace Main
{
    namespace Handlers
    {
        inline void handleItemRepair(const Common::Network::Packet& request, std::shared_ptr<Main::Network::Session> session)
        {
			Common::Network::Packet response;
			response.setTcpHeader(session->getId(), Common::Enums::USER_ENCRYPTION);
			response.setCommand(request.getOrder(), request.getMission(), 1, 1);
			const auto serialInfo = Main::Details::parseData<Main::Structures::ItemSerialInfo>(request);

			if (auto idAndDurability = session->getPlayer().findItemIdAndDurabilityBySerialInfo(serialInfo))
			{
				const auto baseItemDurability = Main::CdbUtils::getItemDurability(idAndDurability->first);
				if (!baseItemDurability)
				{
					session->sendMessage("[Handlers::repairItem] baseItemDurability was nullopt - please report this issue");
					return;
				}

				const std::uint32_t mpNeededToRepair = *baseItemDurability - idAndDurability->second;
				const auto ainfo = session->getAccountInfo();
				if (ainfo.microPoints >= mpNeededToRepair)
				{
					Main::ClientData::ItemRepair itemRepair{ ainfo.rockTotens, ainfo.microPoints - mpNeededToRepair, serialInfo };
					response.setData(reinterpret_cast<std::uint8_t*>(&itemRepair), sizeof(itemRepair));
					session->setAccountMicroPoints(ainfo.microPoints - mpNeededToRepair);
					session->updateItemDurability(serialInfo.itemNumber, *baseItemDurability);
				}
				else
				{
					Main::ClientData::ItemRepair itemRepair{ ainfo.rockTotens, ainfo.microPoints, Main::Structures::ItemSerialInfo{} };
					response.setData(reinterpret_cast<std::uint8_t*>(&itemRepair), sizeof(itemRepair));
				}
			}
			else
			{
				session->sendMessage("[Handlers::repairItem] idAndDurability was nullopt - please report this issue");
				return;
			}
			session->asyncWrite(response);
        }
    }
}

#endif