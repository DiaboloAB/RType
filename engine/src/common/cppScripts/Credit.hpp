/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CREDIT_HPP
#define CREDIT_HPP

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class CreditScript : public RType::ICppScript
{
   public:
    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._runtime->getKey(KeyCode::DownArrow))
        {
            auto &transform = registry.get<Transform>(_entity);
            transform.position.y -= 100 * gameContext._deltaT;
        }
        if (gameContext._runtime->getKey(KeyCode::Escape))
        {
            gameContext._sceneManager._nextScene = "menu.json";
        }
    }
    void setEntity(mobs::Entity entity) override { _entity = entity; }

   private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif  // CREDIT_HPP