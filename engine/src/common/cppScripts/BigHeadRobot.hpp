/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef BIGHEADROBOT_HPP
#define BIGHEADROBOT_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/GetCppScript.hpp"

namespace RType
{

class BigHeadRobot : public RType::ICppScript
{
   public:
    virtual void onCollisionEnter(mobs::Registry &registry, GameContext &gameContext,
                                  mobs::Entity other) override
    {
        auto &animations = registry.get<Animator>(getEntity()).animations;

        animations.playAnim("explosion");
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 50;

        auto &transform = registry.get<Transform>(getEntity());
        auto &basics = registry.get<Basics>(getEntity());

        float deltaX = CoordonatePlayer(registry).x - transform.position.x;
        float deltaY = CoordonatePlayer(registry).y - transform.position.y;
        
        double v = 3.0;

        double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        if (distance != 0) {
            double directionX = deltaX / distance;
            double directionY = deltaY / distance;
            transform.position.x += directionX * v;
            transform.position.y += directionY * v;
        }

        if (!timer.getState())
        {
            timer.start();
        }

        timer.update(gameContext._deltaT);

        if (timer.getTime() > 2)
        {
            timer.reset();
            mobs::Entity entity = gameContext._sceneManager.instantiate("Bullet", gameContext);

            auto &bulletBasic = registry.get<Basics>(entity);
            auto &bulletTransform = registry.get<Transform>(entity);
            auto &entityScript = registry.get<CppScriptComponent>(entity);

            bulletTransform.position = transform.position + mlg::vec3(-20, 32, 0);
            try
            {
                getCppScriptById<Bullet>(entity, registry)
                    ->setDirection(computeDirection(transform.position, registry));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

        if (transform.position.x < -100)
        {
            registry.kill(getEntity());
        }
    }

    static constexpr const char *name = "BigHeadRobot";

   private:
    Timer timer;

    mlg::vec3 computeDirection(mlg::vec3 &position, mobs::Registry &registry)
    {
        auto view = registry.view<Basics, Transform>();

        for (auto entity : view)
        {
            auto &basics = view.get<Basics>(entity);
            if (basics.tag == "player")
            {
                auto &playerTransform = view.get<Transform>(entity);
                mlg::vec3 newPos = playerTransform.position - position;
                return newPos.normalize();
            }
        }
        std::cerr << "Player not found" << std::endl;
        return mlg::vec3(0.0f);
    }

    mlg::vec3 CoordonatePlayer(mobs::Registry &registry)
    {
        auto view = registry.view<Basics, Transform>();

        for (auto entity : view)
        {
            auto &basics = view.get<Basics>(entity);
            if (basics.tag == "player")
            {
                auto &playerTransform = view.get<Transform>(entity);
                return playerTransform.position;
            }
        }
        std::cerr << "Player not found" << std::endl;
        return mlg::vec3(0.0f);
    }
};

}  // namespace RType

#endif  // BIGHEADROBOT_HPP