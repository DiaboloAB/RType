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


    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._networkHandler == nullptr)
            return;
        if (gameContext._networkHandler->getIsServer())
            std::cout << "Je suis un server" << std::endl;
        else
            std::cout << "Je suis un client" << std::endl;
    }

   private:
};
}

#endif  // NETWORKSYSTEM_H