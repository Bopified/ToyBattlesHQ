#ifndef CGD_EVENTMISSIONINFO_H
#define CGD_EVENTMISSIONINFO_H

#include "visit_struct/visit_struct.hpp"

namespace Common
{
	namespace ConstantDatabase
	{
#pragma pack(push, 1)
		struct CdbEventMissionInfo
		{
			std::uint32_t em_id = static_cast<std::uint32_t>(-1);
			char em_name[250]{};
			std::uint32_t em_dropitemid{};
			std::uint32_t em_num{};
			std::uint32_t em_rewardid{};
			std::uint32_t em_icon{};

			constexpr std::uint32_t getId() const noexcept { return em_id; }
			constexpr bool isValid() const noexcept { return em_id != static_cast<std::uint32_t>(-1); }
		};
#pragma pack(pop)
	}
}

VISITABLE_STRUCT(Common::ConstantDatabase::CdbEventMissionInfo, em_id, em_name, em_dropitemid, em_num, em_rewardid, em_icon);

#endif