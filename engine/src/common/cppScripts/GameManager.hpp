/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "common/components.hpp"

namespace RType
{

class GameManager : public RType::ICppScript
{
public:
    GameManager() {}
    ~GameManager() {}

    void start(mobs::Registry &registry, GameContext &gameContext) override {
        try {
            std::cout << "GameManager audio" << std::endl;
            Audio &audio = registry.get<Audio>(_entity);
            audio.audioQueue.push("assets/sounds/menu.ogg");
            std::cout << "GameManager audio queue length: " << audio.audioQueue.size() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {

    }

    void setEntity(mobs::Entity entity) override { _entity = entity; }
private:
    mobs::Entity _entity;
};

}  // namespace RType

#endif // GAMEMANAGER_H