#ifndef CAPSULE_LIST_STRUCT_H
#define CAPSULE_LIST_STRUCT_H

#include <cstdint>

namespace Main
{
	namespace Structures
	{
#pragma pack(push, 1)
		struct CapsuleList
		{
			std::uint32_t capsuleInfoId = 0;
			std::uint32_t newPrice : 21 = 0;
			std::uint32_t unknown2 : 11 = 0;
			std::uint32_t saleEventStartDate{};
			std::uint32_t saleEventEndDate{};
		};
#pragma pack(pop)

#pragma pack(push, 1)
		struct CapsuleListDatabase
		{
			std::uint32_t newRtPrice{};
			std::uint32_t newMpPrice{};
			std::uint32_t saleEventStartDate{};
			std::uint32_t saleEventEndDate{};
		};
#pragma pack(pop)

#pragma pack(push, 1)
		struct EventMissionInfo
		{
			std::uint32_t startDate{};
			std::uint32_t endDate{};
		};
#pragma pack(pop)

#pragma pack(push, 1)
		struct ExpMpBonusInfo
		{
			std::uint32_t startDate{};
			std::uint32_t endDate{};
			std::uint32_t expBonusPercent{};
			std::uint32_t mpBonusPercent{};
		};
#pragma pack(pop)
	}
}

#endif