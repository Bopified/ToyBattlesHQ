#ifndef OBSERVER_MODE_ACTION_CHECK
#define OBSERVER_MODE_ACTION_CHECK

#include "../Interfaces.h"
#include <optional>
#include <string>

namespace Ac
{
    struct ObserverModeActionChecker : public IACChecker<SessionPacket>
    {
        std::optional<ACFlag> processEvent(const SessionPacket& event) override
        {
            if (!event.session)
                return std::nullopt;

            if (event.session->m_team == Common::Enums::Team::TEAM_OBSERVER)
            {
                const ACFlag flag{
                    event.session->getAccountId(),
                    "ObserverModeAction",
                    "Impossible action done while in observer mode detected: " + event.message
                };

                event.session->closeSocket();

                return flag;
            }

            return std::nullopt;
        }
    };
}

#endif
