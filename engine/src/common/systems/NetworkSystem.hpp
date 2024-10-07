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

namespace RType
{

class NetworkSystem : public ISystem
{
   public:
    NetworkSystem() {}
    ~NetworkSystem() {}


    void manageServerQueue(mobs::Registry &registry, GameContext &gameContext)
    {
        std::queue<std::pair<std::shared_ptr<RType::Network::APacket>, asio::ip::udp::endpoint>>
            serverQueue = gameContext._networkHandler->getPacketQueue();

        if (serverQueue.empty())
            std::cout << "J'ai une queue vide" << std::endl;
        return;
    }

    void manageClientQueue(mobs::Registry &registry, GameContext &gameContext)
    {
        // send a first packet to server

        return;
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._networkHandler == nullptr)
            return;
        if (gameContext._networkHandler->getIsServer())
            this->manageServerQueue(registry, gameContext);
        else
            this->manageClientQueue(registry, gameContext);
    }

   private:
};
}

#endif  // NETWORKSYSTEM_H