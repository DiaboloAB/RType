/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <mobs/mobs.hpp>
#include <sceneManager/SceneManager.hpp>
#include <clocksManager/ClockManager.hpp>
#include <input/Input.hpp>

#include "IRuntime/IRuntime.hpp"
#include "common/COMPONENTLIST.hpp"
// std
#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

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
    GameContext(std::string assetsPath, mobs::Registry &registry, SceneManager &sceneManager, ClockManager &clockManager, Input &input,
                std::shared_ptr<IRuntime> runtime = nullptr);

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
            throw std::runtime_error("Tag not found: " + tag);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error(e.what());
        }
    }

    std::string getTag(mobs::Entity entity)
    {
        if (!_registry.hasComponent<Basics>(entity)) return "";
        return _registry.get<Basics>(entity).tag;
    }

    /**
     * @brief Put the entity in the destroy queue.
     *
     * @param entity The entity to destroy.
     */
    void destroyEntity(mobs::Entity entity) { _entitiesToDestroy.push(entity); }

    /**
     * @brief Destroys all entities in the destroy queue.
     */
    void destroyEntities()
    {
        while (!_entitiesToDestroy.empty())
        {
            _registry.kill(_entitiesToDestroy.front());
            _entitiesToDestroy.pop();
        }
    }

    /**
     * @brief Updates the game context.
     */
    void addEvent(std::string event, std::vector<std::variant<float, std::string>> args)
    {
        _events[event] = args;
    }

    /**
     * @brief Checks if an event exists.
     *
     * @param event The event to check.
     * @return true if the event exists, false otherwise.
     */
    bool hasEvent(std::string event) { return _events.find(event) != _events.end(); }

    /**
     * @brief Gets the event.
     *
     * @param event The event to get.
     * @return The event.
     */
    std::vector<std::variant<float, std::string>> getEvent(std::string event)
    {
        return _events[event];
    }

    /**
     * @brief Clears all events.
     */
    void clearEvents() { _events.clear(); }

    float getGameSpeed() const { return _gameSpeed; }

    void setGameSpeed(float gameSpeed) { _gameSpeed = gameSpeed; }

    std::shared_ptr<IRuntime> _runtime;  ///< The runtime.
    mobs::Registry &_registry;           ///< The registry.
    SceneManager &_sceneManager;         ///< The scene manager.
    ClockManager &_clockManager;          ///< The clock manager.
    Input &_input;                        ///< The input manager.

    bool _running = true;  ///< The running state.
    float _deltaT = 0.0f;  ///< The delta time.
    const std::string _assetsPath;
    std::map<std::string, std::string> _args;  ///< The arguments.
    int _systemCount = 0;                        ///< The number of systems.

   private:
    std::unordered_map<std::string, std::vector<std::variant<float, std::string>>> _events;  ///< The events.

    float _gameSpeed = 1.0f;  ///< The game speed.
    std::queue<mobs::Entity> _entitiesToDestroy;  ///< The entities to destroy.
};

}  // namespace RType

#endif  // GAMECONTEXT_H
