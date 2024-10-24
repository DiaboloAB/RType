/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include <NetworkEvents/NetworkEventHandler.hpp>
#include <NetworkHandler/EndpointState.hpp>
#include <NetworkHandler/NetworkIdHandler.hpp>
#include <NetworkPacketManager/APacket.hpp>
#include <NetworkPacketManager/CreateEntityPacket.hpp>
#include <NetworkPacketManager/DestroyEntityPacket.hpp>
#include <NetworkPacketManager/HiClientPacket.hpp>
#include <NetworkPacketManager/HiServerPacket.hpp>
#include <NetworkPacketManager/PacketValidationPacket.hpp>
#include <common/components.hpp>
#include <mobs/mobs.hpp>
#include <system/ISystem.hpp>

namespace RType
{

class NetworkSystem : public ISystem
{
   public:
    NetworkSystem()
        : _idHandler(Network::NetworkIdHandler()),
          _eventHandler(Network::NetworkEventHandler(_idHandler))
    {
        this->_systemsMap[Network::HISERVER] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleHiServer(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::HICLIENT] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleHiClient(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::ADIOSSERVER] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleAdiosServer(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::PING] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handlePing(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::CREATEENTITY] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleCreateEntity(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::DESTROYENTITY] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleDestroyEntity(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::MOVEENTITY] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleMoveEntity(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::UPDATEENTITY] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleUpdateEntity(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::CLIENTEVENT] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handleClientEvent(packet, sender, registry, gameContext); };
        this->_systemsMap[Network::PACKETVALIDATION] =
            [this](std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                   mobs::Registry &registry, GameContext &gameContext)
        { handlePacketValidation(packet, sender, registry, gameContext); };
    }

    ~NetworkSystem() {}

    /**
     * @brief HiServer packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleHiServer(std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                        mobs::Registry &registry, GameContext &gameContext)
    {
        if (!gameContext._networkHandler->getIsServer()) return;
        std::map<asio::ip::udp::endpoint, Network::EndpointState> endpointMap =
            gameContext._networkHandler->getEndpointMap();
        Network::HiClientPacket packetToSend;
        if (endpointMap.count(sender) == 0)
            gameContext._networkHandler->updateEndpointMap(sender, false);
        gameContext._networkHandler->sendNewPacket(packetToSend, sender);
        std::cerr << "[NETWORK LOG] HiServer : New client set." << std::endl;
    }

    /**
     * @brief HiClient packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleHiClient(std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                        mobs::Registry &registry, GameContext &gameContext)
    {
        if (gameContext._networkHandler->getIsServer()) return;
        std::map<asio::ip::udp::endpoint, Network::EndpointState> endpointMap =
            gameContext._networkHandler->getEndpointMap();
        Network::PacketValidationPacket packetToSend(Network::HICLIENT,
                                                     packet->getPacketTimeStamp());
        if (endpointMap.count(sender) == 1)
            gameContext._networkHandler->updateEndpointMap(sender, true);
        gameContext._networkHandler->sendNewPacket(packetToSend, sender);
        std::cerr << "[NETWORK LOG] Client connected to server !" << std::endl;
    }

    /**
     * @brief AdiosServer packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleAdiosServer(std::shared_ptr<Network::APacket> &packet,
                           asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                           GameContext &gameContext)
    {
        if (!gameContext._networkHandler->getIsServer()) return;

        std::map<asio::ip::udp::endpoint, Network::EndpointState> endpointMap =
            gameContext._networkHandler->getEndpointMap();

        auto target = endpointMap.find(sender);
        if (target == endpointMap.end()) return;

        gameContext._networkHandler->removeEndpointFromMap(sender);
        Network::DestroyEntityPacket packetToSend(target->second.getNetworkId());

        if (target->second.getConnected() &&
            gameContext._networkHandler->getGameState() == Network::IN_GAME)
        {
            endpointMap = gameContext._networkHandler->getEndpointMap();
            for (const auto &endpoint : endpointMap)
            {
                gameContext._networkHandler->sendNewPacket(packetToSend, endpoint.first);
            }
        }
    }

    /**
     * @brief Ping packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handlePing(std::shared_ptr<Network::APacket> &packet, asio::ip::udp::endpoint &sender,
                    mobs::Registry &registry, GameContext &gameContext)
    {
        std::map<asio::ip::udp::endpoint, Network::EndpointState> endpointMap =
            gameContext._networkHandler->getEndpointMap();

        auto target = endpointMap.find(sender);
        if (target == endpointMap.end() || !target->second.getConnected()) return;
        gameContext._networkHandler->updateEndpointMap(sender, true);
        std::cerr << "[NETWORK LOG] Ping recep !" << std::endl;
    }

    /**
     * @brief CreateEntity packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleCreateEntity(std::shared_ptr<Network::APacket> &packet,
                            asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                            GameContext &gameContext)
    {
        try
        {
            std::shared_ptr<Network::CreateEntityPacket> createPacket =
                std::dynamic_pointer_cast<Network::CreateEntityPacket>(packet);
            mobs::Registry::View view = registry.view<NetworkComp>();
            for (auto &entity : view)
            {
                auto &networkC = view.get<NetworkComp>(entity);
                if (networkC.id == createPacket->getEntityId())
                {
                    auto validation = Network::PacketValidationPacket(
                        createPacket->getPacketType(), createPacket->getPacketTimeStamp());
                    gameContext._networkHandler->sendNewPacket(validation, sender);
                    return;
                }
            }
            mobs::Entity newEntity = gameContext._sceneManager.loadPrefab(
                createPacket->getEntityToCreate(), gameContext);
            auto &transform = registry.get<Transform>(newEntity);
            transform.position = mlg::vec3(createPacket->getPosX(), createPacket->getPosY(), 0.0f);
            auto &networkComp = registry.get<NetworkComp>(newEntity);
            networkComp.id = createPacket->getEntityId();
            auto validation = Network::PacketValidationPacket(createPacket->getPacketType(),
                                                              createPacket->getPacketTimeStamp());
            gameContext._networkHandler->sendNewPacket(validation, sender);
            std::cerr << "[NETWORK LOG] Entity Created !" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "[NETWORK LOG] CREATE ERR : " << e.what() << std::endl;
        }
    }

    /**
     * @brief DestroyEntity packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleDestroyEntity(std::shared_ptr<Network::APacket> &packet,
                             asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                             GameContext &gameContext)
    {
        try
        {
            std::shared_ptr<Network::DestroyEntityPacket> destroyPacket =
                std::dynamic_pointer_cast<Network::DestroyEntityPacket>(packet);
            if (this->getActualTime() - destroyPacket->getPacketTimeStamp() >= 4) return;
            mobs::Registry::View view = registry.view<NetworkComp>();
            for (auto &entity : view)
            {
                auto &networkC = view.get<NetworkComp>(entity);
                if (networkC.id == destroyPacket->getEntityId()) registry.kill(entity);
            }
            auto validation = Network::PacketValidationPacket(destroyPacket->getPacketType(),
                                                              destroyPacket->getPacketTimeStamp());
            gameContext._networkHandler->sendNewPacket(validation, sender);
            std::cerr << "[NETWORK LOG] Entity Destroy !" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "[NETWORK LOG] DESTROY ERR : " << e.what() << std::endl;
        }
    }

    /**
     * @brief MoveEntity packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleMoveEntity(std::shared_ptr<Network::APacket> &packet,
                          asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                          GameContext &gameContext)
    {
        try
        {
            std::shared_ptr<Network::MoveEntityPacket> movePacket =
                std::dynamic_pointer_cast<Network::MoveEntityPacket>(packet);
            if (this->getActualTime() - movePacket->getPacketTimeStamp() >= 2) return;
            mobs::Registry::View view = registry.view<NetworkComp>();
            for (auto &entity : view)
            {
                auto &networkC = view.get<NetworkComp>(entity);
                if (networkC.id == movePacket->getEntityId())
                {
                    auto &transform = view.get<Transform>(entity);
                    transform.position.x = movePacket->getPosX();
                    transform.position.y = movePacket->getPosY();
                    try
                    {
                        std::cerr << "[NETWORK LOG] Entity Move !" << std::endl;
                        auto &ally = view.get<Ally>(entity);
                        ally.moveDirection.x = movePacket->getDirectionX();
                        ally.moveDirection.y = movePacket->getDirectionY();
                    }
                    catch (std::exception &e)
                    {
                        std::cerr << "[NETWORK LOG] No ally component" << std::endl;
                    }
                    return;
                }
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "[NETWORK LOG] Error while moving entity : " << e.what() << std::endl;
        }
    }

    /**
     * @brief UpdateEntity packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleUpdateEntity(std::shared_ptr<Network::APacket> &packet,
                            asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                            GameContext &gameContext)
    {
        return;
    }

    /**
     * @brief ClientEvent packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handleClientEvent(std::shared_ptr<Network::APacket> &packet,
                           asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                           GameContext &gameContext)
    {
        try
        {
            std::shared_ptr<Network::ClientEventPacket> eventPacket =
                std::dynamic_pointer_cast<Network::ClientEventPacket>(packet);
            this->_eventHandler.update(eventPacket->getClientEvent(), sender, registry,
                                       gameContext);
            // std::cerr << "[NETWORK LOG] Client event !" << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << "[NETWORK LOG] Error in client event !" << std::endl;
        }
    }

    /**
     * @brief PacketValidation packet handler.
     *
     * @param packet: Packet received.
     * @param sender: Endpoint of the packet sender.
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void handlePacketValidation(std::shared_ptr<Network::APacket> &packet,
                                asio::ip::udp::endpoint &sender, mobs::Registry &registry,
                                GameContext &gameContext)
    {
        try
        {
            std::shared_ptr<Network::PacketValidationPacket> validation =
                std::dynamic_pointer_cast<Network::PacketValidationPacket>(packet);
            if (this->getActualTime() - validation->getPacketTimeStamp() >= 4) return;
            if (validation->getPacketReceiveType() == Network::HICLIENT)
            {
                gameContext._networkHandler->updateEndpointMap(sender, true);
            }
            gameContext._networkHandler->deleteFromValidationList(validation, sender);
        }
        catch (std::exception &e)
        {
            std::cerr << "[NETWORK LOG] VALIDATION ERR : " << e.what() << std::endl;
        }
    }

    /**
     * @brief Method that take each packet from NetworkHandler queue and call it's associated
     * method.
     *
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void manageQueue(mobs::Registry &registry, GameContext &gameContext)
    {
        // std::cerr << "JE LOG AU DEBUT DE MANAGE" << std::endl;
        std::queue<std::pair<std::shared_ptr<Network::APacket>, asio::ip::udp::endpoint>>
            packetQueue = gameContext._networkHandler->getPacketQueue();

        std::shared_ptr<Network::APacket> packet;
        asio::ip::udp::endpoint sender;
        Network::PacketType type;

        while (!packetQueue.empty())
        {
            try
            {
                packet = packetQueue.front().first;
                sender = packetQueue.front().second;
                type = packet->getPacketType();
                this->_systemsMap[type](packet, sender, registry, gameContext);
            }
            catch (std::exception &e)
            {
                std::cerr << "[manageQueue ERROR] Unable to get packet or packetType" << std::endl;
                packetQueue.pop();
                gameContext._networkHandler->popQueue();
                continue;
            }

            try
            {
                packetQueue.pop();
                gameContext._networkHandler->popQueue();
            }
            catch (std::exception &e)
            {
                std::cerr << "[manageQueue ERROR] Problem when removing packets from queue."
                          << std::endl;
                return;
            }
        }
        // std::cerr << "JE LOG A LA FIN DE MANAGE" << std::endl;
        return;
    }

    /**
     * @brief Method that update game content based on packets received by calling the queue
     * manager.
     *
     * @param registry: Entity handler.
     * @param gameContext: Object that allow access to engine attributes & methods.
     *
     */
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._networkHandler == nullptr) return;
        this->manageQueue(registry, gameContext);
    }

    uint64_t getActualTime()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

   private:
    std::unordered_map<Network::PacketType, std::function<void(std::shared_ptr<Network::APacket> &,
                                                               asio::ip::udp::endpoint &,
                                                               mobs::Registry &, GameContext &)>>
        _systemsMap;
    Network::NetworkIdHandler _idHandler;
    Network::NetworkEventHandler _eventHandler;
};
}  // namespace RType

#endif  // NETWORKSYSTEM_H