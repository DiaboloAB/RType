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

namespace RType
{

class Turret : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 50;

        auto &transform = registry.get<Transform>(getEntity());
        auto &basics = registry.get<Basics>(getEntity());
        transform.position.x -= speed * gameContext._deltaT;

        double deltaX = computeDirection(transform.position, registry).x - transform.position.x;
        double deltaY = computeDirection(transform.position, registry).y - transform.position.y;

        double theta = std::atan2(deltaY, deltaX);

        double thetaDegrees = theta * 180.0 / M_PI;

        if ((theta >= 0 && theta < 45) || (theta >= 315 && theta < 360)) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 45 && theta < 90) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 90 && theta < 135) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 135 && theta < 180) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 180 && theta < 225) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 225 && theta < 270) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 270 && theta < 315) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        } else if (theta >= 315 && theta < 360) {
            AnimationList &animations = registry.get<Animator>(getEntity()).animations;
            animations.playAnim("low");
        }

        if (thetaDegrees < 0) {
            thetaDegrees += 360.0;
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
};

}  // namespace RType

#endif  // REDSHIP_HPP