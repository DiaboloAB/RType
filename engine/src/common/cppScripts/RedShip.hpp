/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef REDSHIP_HPP
#define REDSHIP_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/GetCppScript.hpp"
#include "common/cppScripts/Bullet.hpp"

namespace RType
{

class RedShip : public RType::ICppScript
{
   public:
    void onCollisionEnter(mobs::Registry &registry, GameContext &gameContext,
                                  mobs::Entity other) override
    {
        auto &animations = registry.get<Animator>(getEntity()).animations;

        try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
        } catch (const std::exception &e) {}

        NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
        auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
        getCppScriptById<MoveLaser>(other, registry)->reduceHealth(registry, 1);

        auto createServ = room.factory.createEmptyPacket<dimension::CreateEntity>();
        uint32_t id = room.idFactory.generateNetworkId();
        auto &transform = registry.get<Transform>(getEntity());
        createServ->setNetworkId(id);
        createServ->setEntityToCreate("Explosion");
        createServ->setPosX(transform.position.x);
        createServ->setPosY(transform.position.y);
        createServ->setScaleX(1);
        createServ->setScaleY(1);
        room.room->sendToAll(createServ);

        killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
        room.room->sendToAll(killServe);
        registry.kill(getEntity());
    }

    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        timer.start();
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 100;

        auto &transform = registry.get<Transform>(getEntity());
        auto &basics = registry.get<Basics>(getEntity());
        transform.position.x -= speed * gameContext._deltaT;

        try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
        } catch (const std::exception &e) {
        }

        timer.update(gameContext._deltaT);

        if (timer.getTime() > 1.75)
        {
            timer.reset();

            auto view = registry.view<Basics, Transform>();

            for (auto entity : view)
            {
                auto &basics = view.get<Basics>(entity);
                if (basics.tag == "ally")
                {
                    mobs::Entity bullet = gameContext._sceneManager.instantiate("Bullet", gameContext);

                    auto &bulletTransform = registry.get<Transform>(bullet);
                    auto &networkData = registry.get<NetworkData>(bullet);
                    auto &playerTransform = registry.get<Transform>(entity);


                    bulletTransform.position = transform.position + mlg::vec3(-20, 32, 0);
                    try
                    {
                        mlg::vec3 direction = computeDirection(transform.position, playerTransform.position);
                        getCppScriptById<Bullet>(bullet, registry)
                            ->setDirection(direction);

                        NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
                        uint32_t networkId = room.idFactory.generateNetworkId();
                        networkData._id = networkId;
                        sendBulletSpawn(registry, "Bullet", bulletTransform.position, networkId, room);
                        sendBulletMove(registry, bullet, bulletTransform.position, direction, networkId, room);
                    }
                    catch (const std::exception &e)
                    {
                        std::cerr << e.what() << std::endl;
                    }
                }
            }
        }

        try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
        } catch (const std::exception &e) {}
        if (transform.position.x < -100)
        {
            NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
            auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();
            killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
            room.room->sendToAll(killServe);

            registry.kill(getEntity());
        }
    }

    void onButtonPressed(
        mobs::Registry &registry, GameContext &gameContext, std::string action,
        const std::vector<std::variant<mlg::vec3, int, std::string>> &args) override
    {
        if (action == "move" && args.size() >= 1)
        {
            auto position = std::get<mlg::vec3>(args[0]);

            setPosition(registry, position);
        }
    }

    static constexpr const char *name = "RedShip";

   private:
    Timer timer;

    mlg::vec3 computeDirection(mlg::vec3 &position, mlg::vec3& playerPosition)
    {
        mlg::vec3 newPos = playerPosition - mlg::vec3(0, 20, 0) - position;
        return newPos.normalize();
    }

    void setPosition(mobs::Registry &registry, mlg::vec3 NewPosition)
    {
        auto &transform = registry.get<Transform>(getEntity());

        transform.position = NewPosition;
    }

    void sendBulletSpawn(mobs::Registry &registry, std::string prefab, mlg::vec3 position, uint32_t networkId, NetworkRoom &room)
    {
        auto spawnServe = room.factory.createEmptyPacket<dimension::CreateEntity>();

        spawnServe->setNetworkId(networkId);
        spawnServe->setEntityToCreate(prefab);
        spawnServe->setPosX(position.x);
        spawnServe->setPosY(position.y);
        spawnServe->setScaleX(1);
        spawnServe->setScaleY(1);

        room.room->sendToAll(spawnServe);
    }

    void sendBulletMove(mobs::Registry &registry, mobs::Entity entity, mlg::vec3 position, mlg::vec3 direction, uint32_t networkId, NetworkRoom &room)
    {
        auto moveServe = room.factory.createEmptyPacket<dimension::MoveEntity>();

        moveServe->setNetworkId(networkId);
        moveServe->setPosX(position.x);
        moveServe->setPosY(position.y);
        moveServe->setDirectionX(direction.x);
        moveServe->setDirectionY(direction.y);

        room.room->sendToAll(moveServe);
    }
};

}  // namespace RType

#endif  // REDSHIP_HPP