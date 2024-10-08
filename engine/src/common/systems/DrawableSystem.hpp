/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef DRAWABLESYSTEM_H
#define DRAWABLESYSTEM_H

#include "common/components.hpp"
#include <system/ISystem.hpp>
// std

namespace RType
{

class DrawableSystem : public ISystem
{
public:
    DrawableSystem() {}
    ~DrawableSystem() {}


    void draw(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Button>();
        for (auto entity : view)
        {
            auto &button = view.get<Button>(entity);
            // gameContext._runtime->drawText(button.text, button.position);
        }
    }
    // Getters

    // Setters

private:
    // Member variables
};

}

#endif // DRAWABLESYSTEM_H