#ifndef AC_AC_BASE_H
#define AC_AC_BASE_H

#include "AcEventQueue.h"
#include "Interfaces.h"
#include "Interfaces.h"
#include <iostream>
#include "Checks/PacketFloodingCheck.h"

namespace Ac
{
    class AntiCheatManager 
    {
    private:
        ACEventQueue eventQueue;
        std::vector<std::unique_ptr<IACCheckerBase>> checkers;
        std::thread workerThread;
        std::atomic<bool> running{ false };

        AntiCheatManager(const AntiCheatManager&) = delete;
        AntiCheatManager& operator=(const AntiCheatManager&) = delete;

        void worker()
        {
            while (running) 
            {
                auto event = eventQueue.popEvent();
                if (!event) continue;

                for (auto& checker : checkers) 
                {
                    if (auto flag = checker->processEventBase(*event)) 
                    {
                        handleFlag(*flag);
                    }
                }
            }
        }

        void handleFlag(const ACFlag& flag) 
        {
            std::cout << "AC Flag: " << flag.cheatType
                << " for player " << flag.sessionId
                << " - " << flag.details << std::endl;
        }

    public:
        AntiCheatManager() 
        {
            registerChecker<PacketFloodChecker>();
            // registerChecker<AimBotChecker>();
            // registerChecker<TeleportChecker>();

            running = true;
            workerThread = std::thread(&AntiCheatManager::worker, this);
        }

        ~AntiCheatManager()
        {
            running = false;
            eventQueue.shutdown();
            if (workerThread.joinable()) workerThread.join();
        }

        template<typename CheckerT>
        void registerChecker() 
        {
            checkers.push_back(std::make_unique<CheckerT>());
        }

        void submitEvent(std::unique_ptr<ACEvent> event) 
        {
            eventQueue.pushEvent(std::move(event));
        }
    };
}


#endif