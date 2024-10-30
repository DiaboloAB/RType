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

class RedShip : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        int speed = 100;

        auto &transform = registry.get<Transform>(getEntity());
        auto &basics = registry.get<Basics>(getEntity());
        transform.position.x -= speed * gameContext._deltaT;

        if (!timer.getState())
        {
            timer.start();
        }

        timer.update(gameContext._deltaT);

        if (timer.getTime() > 2)
        {
            timer.reset();
            std::cout << "Creating bullet | ship :" << basics.tag << std::endl;
            mobs::Entity entity = gameContext._sceneManager.instantiate("Bullet", gameContext);
            std::string toPrint = "bullet :" + basics.tag + "_bullet" + std::to_string(bullet_index);
            std::cout << toPrint << " created" << std::endl;

            auto &bulletBasic = registry.get<Basics>(entity);
            auto &bulletTransform = registry.get<Transform>(entity);
            auto &entityScript = registry.get<CppScriptComponent>(entity);

            bulletTransform.position = transform.position + mlg::vec3(-20, 32, 0);
            bulletBasic.tag = basics.tag + "_bullet" + std::to_string(bullet_index);
            try
            {
                std::cout << "Setting direction for bullet: " << basics.tag + "_bullet" + std::to_string(bullet_index) << std::endl;
                getCppScriptById<Bullet>(entity, registry)->setDirection(computeDirection(transform.position, registry));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
            bullet_index++;
            std::cout << "Bullet created" << std::endl;
            std::cout << " " << std::endl;
        }


        if (transform.position.x < -100)
        {
            registry.kill(getEntity());
        }
    }

    static constexpr const char *name = "RedShip";

   private:
    Timer timer;
    int bullet_index = 0;

    mlg::vec3 computeDirection(mlg::vec3 &position, mobs::Registry &registry) {
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