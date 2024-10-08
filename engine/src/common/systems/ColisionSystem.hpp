/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COLISIONSYSTEM_H
#define COLISIONSYSTEM_H

#include <system/ISystem.hpp>
// std

namespace RType
{

class ColisionSystem : public ISystem
{
   public:
    ColisionSystem() {}
    ~ColisionSystem() {}

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Hitbox, Transform>();
        for (auto entity : view)
        {
            for (auto entity2 : view)
            {
                if (entity == entity2)
                    continue;

                auto &transform1 = registry.get<Transform>(entity);
                auto &transform2 = registry.get<Transform>(entity2);
                auto &hitbox1 = registry.get<Hitbox>(entity);
                auto &hitbox2 = registry.get<Hitbox>(entity2);

                if (intersect(transform1, transform2, hitbox1, hitbox2))
                {
                    std::cout << "COLISION" << std::endl;
                }
            }
        }
    }

   private:
    // Member variables
    bool intersect(Transform &transform1, Transform &transform2, Hitbox &hitbox1, Hitbox &hitbox2)
    {
        if (transform1.position.x + hitbox1.size.x > transform2.position.x &&
            transform1.position.x < transform2.position.x + hitbox2.size.x &&
            transform1.position.y + hitbox1.size.y > transform2.position.y &&
            transform1.position.y < transform2.position.y + hitbox2.size.y)
        {
            return true;
        }
        return false;
    }
};

}  // namespace RType

#endif  // COLISIONSYSTEM_H