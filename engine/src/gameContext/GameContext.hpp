/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <RenderSystemSFML/RenderSystemSFML.hpp>
#include <mobs/mobs.hpp>
#include <sceneManager/SceneManager.hpp>

#include "common/components.hpp"
// std
#include <chrono>

namespace RType
{
class GameContext
{
   public:
    GameContext(mobs::Registry &registry, SceneManager &sceneManager);
    ~GameContext();

    void update();

    template <typename Component>
    Component &get(std::string tag)
    {
        try
        {
            mobs::Registry::View view = _registry.view<Basics, Component>();
            for (auto entity : view)
            {
                auto &basics = view.get<Basics>(entity);
                if (basics.tag == tag) return view.get<Component>(entity);
            }
            throw std::runtime_error("Tag not found");
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Tag not found");
        }
    }

    float _deltaT;

    float _drawDeltaT;
    float _updateDeltaT;

    float _targetUpdateDeltaT = 1.0f / 120.0f;
    float _targetDrawDeltaT = 1.0f / 60.0f;

    IRuntime *_runtime;
    mobs::Registry &_registry;
    SceneManager &_sceneManager;

   private:
    std::chrono::high_resolution_clock::time_point _currentTime;

    void loadFonts();
};

}  // namespace RType

#endif  // GAMECONTEXT_H
