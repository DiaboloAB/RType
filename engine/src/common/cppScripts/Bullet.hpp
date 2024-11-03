/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef BULLET_HPP
#define BULLET_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/GetCppScript.hpp"

namespace RType
{

class Bullet : public RType::ICppScript
{
   public:
    void setDirection(const mlg::vec3 &direction) { this->direction = direction; }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 500;

        auto &transform = registry.get<Transform>(getEntity());

        transform.position += direction * speed * gameContext._deltaT;

        /// TODO : server responsability
        if (outOfBounds(transform.position))
        {
            registry.kill(getEntity());
        }
    }

    void onCollisionEnter(mobs::Registry &registry, GameContext &gameContext, mobs::Entity other) override
    {
        try {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");

            if (networkC.client->_serverEndpoint) {
                return;
            }
        } catch (const std::exception &e) {
        }


        auto &basics = registry.get<Basics>(other);

        if (basics.tag == "ally")
        {
            NetworkRoom &room = registry.get<NetworkRoom>(registry.view<NetworkRoom>().front());
            auto killServe = room.factory.createEmptyPacket<dimension::DestroyEntity>();

            killServe->setNetworkId(registry.get<NetworkData>(getEntity())._id);
            room.room->sendToAll(killServe);

            killServe->setNetworkId(registry.get<NetworkData>(other)._id);
            room.room->sendToAll(killServe);

            registry.kill(other);
            registry.kill(getEntity());
        }
    }

    void onButtonPressed(
        mobs::Registry &registry, GameContext &gameContext, std::string action,
        const std::vector<std::variant<mlg::vec3, int, std::string>> &args) override
    {
        if (action == "move" && args.size() >= 2)
        {
            auto position = std::get<mlg::vec3>(args[0]);
            auto direction = std::get<mlg::vec3>(args[1]);

            checkPosition(registry, position, direction);
        }
    }

    static constexpr const char *name = "Bullet";

   private:
    mlg::vec3 direction = mlg::vec3(0.0f);

    bool outOfBounds(const mlg::vec3 &position)
    {
        return position.x < 0 || position.x > 1920 || position.y < 0 || position.y > 1080;
    }

    void checkPosition(mobs::Registry &registry, mlg::vec3 NewPosition, mlg::vec3 NewDirection)
    {
        auto &transform = registry.get<Transform>(getEntity());

        if (NewPosition != transform.position)
        {
            transform.position = NewPosition;
        }
        if (direction.x == 0 && direction.y == 0)
        {
            direction = NewDirection;
        }
    }
};

}  // namespace RType

#endif  // BULLET_HPP