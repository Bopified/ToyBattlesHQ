
#ifndef REST_STRUCTS_H
#define REST_STRUCTS_H

#include <cstdint>
#include "../../../MainServer/include/Structures/AccountInfo/MainAccountUniqueId.h"


namespace Cast
{
    namespace Structures
    {
#pragma pack(push, 1)
        struct SpecialItem // Used to send special items for assassin mode
        {
            std::uint32_t number{};
            std::uint32_t itemId{};
            Main::Structures::UniqueId uid{};
        };
#pragma pack(pop)

#pragma pack(push, 1)
        struct SpecialItemUse
        {
            std::uint32_t itemId{};
            Main::Structures::UniqueId uid{};
        };
#pragma pack(pop)

        struct RespawnCoord 
        {
            std::int32_t x;
            std::int32_t y;
            std::int32_t z;
            std::int32_t w = 0;
        };
    }
}

#endif