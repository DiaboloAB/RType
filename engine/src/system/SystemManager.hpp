/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "ISystem.hpp"

// std
#include <memory>
#include <vector>

namespace RType
{

/**
 * @class SystemManager
 * @brief Manages all systems in the game engine.
 */
class SystemManager
{
   public:
    /**
     * @brief Constructs a new SystemManager object.
     */
    SystemManager();

    /**
     * @brief Destroys the SystemManager object.
     */
    ~SystemManager();

    /**
     * @brief Adds a new system to the manager.
     *
     * @tparam T The type of the system to add.
     * @tparam Args The types of the arguments to pass to the system's constructor.
     * @param args The arguments to pass to the system's constructor.
     * @return T& A reference to the newly added system.
     */
    template <typename T, typename... Args>
    T &addSystem(Args &&...args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T &ref = *system;
        _systems.push_back(std::move(system));
        return ref;
    }

    /**
     * @brief Stops all systems.
     *
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void stop(mobs::Registry &registry, GameContext &gameContext);

    /**
     * @brief Loads all systems.
     *
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void load(mobs::Registry &registry, GameContext &gameContext);

    /**
     * @brief Updates all systems.
     *
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void update(mobs::Registry &registry, GameContext &gameContext);

    /**
     * @brief Draws all systems.
     *
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void draw(mobs::Registry &registry, GameContext &gameContext);

    /**
     * @brief Handles events for all systems.
     *
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void events(mobs::Registry &registry, GameContext &gameContext);

    /**
     * @brief Gets the number of systems.
     *
     * @return int The number of systems.
     */
    int getSystemCount() const { return _systems.size(); }

   private:
    std::vector<std::unique_ptr<ISystem>> _systems;  ///< Container for all systems.
};

}  // namespace RType

#endif  // SYSTEMMANAGER_H
