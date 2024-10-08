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
            this->_systemsMap[Network::HISERVER] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { handleHiServer(packet, registry, gameContext); };
            this->_systemsMap[Network::HICLIENT] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { handleHiClient(packet, registry, gameContext); };
            this->_systemsMap[Network::ADIOSSERVER] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::PING] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::CREATEENTITY] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::DESTROYENTITY] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::MOVEENTITY] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::UPDATEENTITY] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::CLIENTEVENT] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::KICKCLIENT] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
            this->_systemsMap[Network::PACKETVALIDATION] = [this](std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
            { return; };
        }

        ~NetworkSystem() {}

        /**
        * @brief HiServer packet handler.
        *
        * @param packet: Packet received.
        * @param registry: Entity handler.
        * @param gameContext: Object that allow access to engine attributes & methods.
        * 
        */
        void handleHiServer (std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
        {
            return;
        }

        /**
        * @brief HiClient packet handler.
        *
        * @param packet: Packet received.
        * @param registry: Entity handler.
        * @param gameContext: Object that allow access to engine attributes & methods.
        * 
        */
        void handleHiClient (std::shared_ptr<Network::APacket> &packet, mobs::Registry &registry, GameContext &gameContext)
        {
            return;
        }

        /**
        * @brief Method that take each packet from NetworkHandler queue and call it's associated method.
        *
        * @param registry: Entity handler.
        * @param gameContext: Object that allow access to engine attributes & methods.
        * 
        */
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


        /**
        * @brief Method that update game content based on packets received by calling the queue manager.
        *
        * @param registry: Entity handler.
        * @param gameContext: Object that allow access to engine attributes & methods.
        * 
        */
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