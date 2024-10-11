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
#include <iostream>
#include <memory>

namespace RType
{
class GameContext
{
   public:
    /**
     * @brief Constructs a new GameContext object.
     * 
     * @param registry Reference to the entity-component registry.
     * @param sceneManager Reference to the scene manager.
     * @param runtime Shared pointer to the runtime system. Defaults to nullptr.
     */
    GameContext(mobs::Registry &registry, SceneManager &sceneManager, std::shared_ptr<IRuntime> runtime = nullptr);

    /**
     * @brief Destroys the GameContext object.
     */
    ~GameContext();

    /**
     * @brief Retrieves a component of a specific entity identified by its tag.
     * 
     * @tparam Component The type of the component to retrieve.
     * @param tag The tag of the entity.
     * @return Reference to the component.
     * @throws std::runtime_error if the tag is not found.
     */
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

    std::shared_ptr<IRuntime> _runtime; ///< The runtime.
    mobs::Registry &_registry; ///< The registry.
    SceneManager &_sceneManager; ///< The scene manager.

    float _deltaT = 0.0f; ///< The delta time.
   private:
};

}  // namespace RType

#endif  // GAMECONTEXT_H
