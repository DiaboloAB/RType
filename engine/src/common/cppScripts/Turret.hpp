/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef TURRET_HPP
#define TURRET_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "utils/GetCppScript.hpp"

namespace RType
{

class Turret : public RType::ICppScript
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
        transform.position.x -= speed * gameContext._deltaT;

        float deltaX = CoordonatePlayer(registry).x - transform.position.x;
        float deltaY = CoordonatePlayer(registry).y - transform.position.y;

        float theta = std::atan2(deltaY, deltaX);
        ;

        float thetaDegrees = theta * 180.0 / M_PI;

        if (transform.scale.y < 0)
        {
            thetaDegrees = thetaDegrees * -1;
        }

        if (thetaDegrees >= -90 && thetaDegrees < 35)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("right_down");
        }
        else if (thetaDegrees >= 35 && thetaDegrees < 75)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("down_right_down");
        }
        else if (thetaDegrees >= 75 && thetaDegrees < 105)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("down_down_right");
        }
        else if (thetaDegrees >= 105 && thetaDegrees < 135)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("down_down_left");
        }
        else if (thetaDegrees >= 135 && thetaDegrees < 165)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("left_down");
        }
        else if (thetaDegrees >= 165 && thetaDegrees < -90)
        {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("default");
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

    static constexpr const char *name = "Turret";

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

#endif  // TURRET_HPP