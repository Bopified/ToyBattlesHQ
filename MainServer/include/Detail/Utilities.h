#ifndef DETAILS_HEADER_MAIN_H
#define DETAILS_HEADER_MAIN_H

#include <ConstantDatabase/Structures/SetItemInfo.h>
#include "../Network/MainSession.h"
#include "Network/Packet.h"
#include "Utils/Utils.h"
#include "Utils/Constants.h"
#include <chrono>
#include <format>
#include <array>
#include <vector>
#include <source_location>
#include "../Common/include/Enums/RoomEnums.h"

namespace Main
{
	namespace Classes { class RoomsManager; }
	namespace Details
	{
		enum Orders
		{
			PLAYER_STATE_NOTIFICATION = 312,
			PLAYER_ITEMS_BROADCAST = 414,
		};


		template<typename T, typename PacketType, bool Warn = false>
			requires (std::is_same_v<PacketType, Common::Network::Packet> ||
		std::is_same_v<PacketType, Common::Network::UnecryptedPacket>)
			T parseDataImpl(const PacketType& request, std::uint32_t offset = 0, std::source_location location = std::source_location::current())
		{
			static_assert(std::is_trivially_copyable_v<T>, "Details::parseData requires T to be trivially copyable");

			T t{};
			const std::uint32_t dataSize = request.getDataSize();

			if (offset >= dataSize)
			{
				if constexpr (Warn)
				{
					Utils::Logger::log(std::format(
						"Offset out of bounds! [with offset={}, dataSize={}]",
						offset, dataSize),
						Utils::LogType::Warning,
						std::format("Details::parseData - Caller: {}", location.function_name())
					);
				}
				return t; 
			}

			const std::uint32_t dataAvailable = dataSize - offset;

			if (dataAvailable >= sizeof(T))
			{
				if (Warn && dataAvailable > sizeof(T))
				{
					Utils::Logger::log(std::format(
						"Losing some data because dataAvailable > sizeof(T)! [with dataAvailable={}, sizeof(T)={}, offset={}]",
						dataAvailable, sizeof(T), offset),
						Utils::LogType::Warning,
						std::format("Details::parseData - Caller: {}", location.function_name())
					);
				}

				std::memcpy(&t, request.getData() + offset, sizeof(T));
			}
			else
			{
				if constexpr (Warn)
				{
					Utils::Logger::log(std::format(
						"Data is incomplete because dataAvailable < sizeof(T)! [with dataAvailable={}, sizeof(T)={}, offset={}]",
						dataAvailable, sizeof(T), offset),
						Utils::LogType::Warning,
						std::format("Details::parseData - Caller: {}", location.function_name())
					);
				}

				std::memcpy(&t, request.getData() + offset, dataAvailable);
			}

			return t;
		}


		template<typename T, bool Warn = false>
		T parseData(const Common::Network::Packet& request, std::uint32_t offset = 0, std::source_location location = std::source_location::current())
		{
			return parseDataImpl<T, Common::Network::Packet, Warn>(request, offset, location);
		}

		template<typename T, bool Warn = false>
		T parseData(const Common::Network::UnecryptedPacket& request, std::uint32_t offset = 0, std::source_location location = std::source_location::current())
		{
			return parseDataImpl<T, Common::Network::UnecryptedPacket, Warn>(request, offset, location);
		}

		inline std::uint64_t getUtcTimeMs()
		{
			const auto durationSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
			return static_cast<std::uint64_t>(duration_cast<std::chrono::milliseconds>(durationSinceEpoch).count());
		}

		template<std::size_t N>
		inline std::array<std::uint32_t, N> generateRewards()
		{
			std::array<std::uint32_t, N> rewards{};
			static std::vector<std::uint32_t> predefinedItems;

			if (predefinedItems.empty()) 
			{
				std::ifstream file("../RewardItemIDs.txt");
				if (!file.is_open())
				{
					std::cerr << "[Utilities::generateRewards] error while opening file RewardItemIDs.txt\n";
					return rewards;
				}

				std::string line;
				while (std::getline(file, line)) 
				{
					std::uint32_t itemID = 0;
					auto [ptr, ec] = std::from_chars(line.data(), line.data() + line.size(), itemID);
					if (ec == std::errc()) 
						predefinedItems.push_back(itemID); 
				}
				if (predefinedItems.empty())
				{
					std::cerr << "[Utilities::generateRewards] error: predefinedItems empty, nothing has been parsed\n";
					return rewards;
				}
			}

			static std::mt19937 rng(std::random_device{}());
			static std::uniform_int_distribution<std::size_t> dist(0, predefinedItems.size() - 1);
			std::unordered_set<std::size_t> usedIndexes;

			for (std::size_t i = 0; i < rewards.size(); ++i)
			{
				std::size_t index;
				do {
					index = dist(rng);
				} while (usedIndexes.count(index) > 0); 
				rewards[i] = predefinedItems[index];
				usedIndexes.insert(index); 
			}
			return rewards;
		}

		inline std::vector<Common::Enums::ItemType> getPartTypesWhereSetItemInfoTypeNotNull(const Common::ConstantDatabase::SetItemInfo& entry)
		{
			std::vector<Common::Enums::ItemType> itemTypes;
			if (entry.si_hair != -1) itemTypes.push_back(Common::Enums::HAIR);
			if (entry.si_face != -1) itemTypes.push_back(Common::Enums::FACE);
			if (entry.si_top != -1) itemTypes.push_back(Common::Enums::DRESS);
			if (entry.si_under != -1) itemTypes.push_back(Common::Enums::SKIRT);
			if (entry.si_pants != -1) itemTypes.push_back(Common::Enums::LEGS);
			if (entry.si_boots != -1)itemTypes.push_back(Common::Enums::BOOTS);
			if (entry.si_arms != -1) itemTypes.push_back(Common::Enums::GLOVES);
			if (entry.si_acce_A != -1) itemTypes.push_back(Common::Enums::ACC_UPPER);
			if (entry.si_acce_B != -1) itemTypes.push_back(Common::Enums::ACC_BACK); // Check if this is correct
			if (entry.si_acce_C != -1) itemTypes.push_back(Common::Enums::ACC_WAIST); // Same for this

			return itemTypes;
		}

		void broadcastPlayerItems(Main::Classes::RoomsManager& roomsManager, std::shared_ptr<Main::Network::Session> session, const Common::Network::Packet& request);
	}
}

#endif