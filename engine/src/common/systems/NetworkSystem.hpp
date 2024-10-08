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
        NetworkSystem()
        {
            this->_systemsMap[Network::HISERVER] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::HICLIENT] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::ADIOSSERVER] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::PING] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::CREATEENTITY] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::DESTROYENTITY] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::MOVEENTITY] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::UPDATEENTITY] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::CLIENTEVENT] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::KICKCLIENT] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::PACKETVALIDATION] = [](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
        }

        ~NetworkSystem() {}


        void manageQueue(mobs::Registry &registry, GameContext &gameContext)
        {
            std::queue<std::pair<std::shared_ptr<Network::APacket>, asio::ip::udp::endpoint>>
                packetQueue = gameContext._networkHandler->getPacketQueue();

            std::shared_ptr<Network::APacket> packet;
            Network::PacketType type;

            while (!packetQueue.empty()) {
                try {
                    packet = packetQueue.front().first;
                    type = packet->getPacketType();
                } catch (std::exception &e) {
                    std::cerr << "[manageQueue ERROR] Unable to get packet or packetType" << std::endl;
                    return;
                } 

                try {
                    packetQueue.pop();
                    gameContext._networkHandler->popQueue();
                } catch (std::exception &e) {
                    std::cerr << "[manageQueue ERROR] Problem when removing packets from queue." << std::endl;
                    return;
                }
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
        std::unordered_map<Network::PacketType, std::function<void(std::shared_ptr<Network::APacket> &,
            mobs::Registry &, GameContext &)>> _systemsMap;
};
}

#endif  // NETWORKSYSTEM_H