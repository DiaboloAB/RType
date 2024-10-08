/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include <system/ISystem.hpp>
#include <PacketManager/APacket.hpp>
#include <PacketManager/HiServerPacket.hpp>

namespace RType
{

class NetworkSystem : public ISystem
{
   public:
    NetworkSystem() {}
    ~NetworkSystem() {}


    void manageQueue(mobs::Registry &registry, GameContext &gameContext)
    {
        std::queue<std::pair<std::shared_ptr<RType::Network::APacket>, asio::ip::udp::endpoint>>
            packetQueue = gameContext._networkHandler->getPacketQueue();

        while (!packetQueue.empty()) {
            std::shared_ptr<RType::Network::APacket> packet = packetQueue.front().first;

            // handle le packet en fonction de son type

            packetQueue.pop();
            gameContext._networkHandler->popQueue();
        }
        return;
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._networkHandler == nullptr)
            return;
        this->manageQueue(registry, gameContext);
    }

   private:
};
}

#endif  // NETWORKSYSTEM_H