/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <nlohmann/json.hpp>

#include "common/ICppScript.hpp"
#include "mobs/mobs.hpp"
// std
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace RType
{

class GameContext;

/**
 * @class SceneManager
 * @brief Manages scenes within the game engine.
 */
class SceneManager
{
   public:
    /**
     * @brief The name of the next scene to load.
     */
    std::string _nextScene = "";

    /**
     * @brief Constructs a new SceneManager object.
     */
    SceneManager();

    /**
     * @brief Destroys the SceneManager object.
     */
    ~SceneManager();

    /**
     * @brief Loads a scene by name.
     *
     * @param sceneName The name of the scene to load.
     * @param gameContext The context of the game.
     */
    void loadScene(const std::string &sceneName, GameContext &gameContext);

    /**
     * @brief Loads a prefab by name.
     *
     * @param prefabName The name of the prefab to load.
     * @param gameContext The context of the game.
     * @return mobs::Entity The entity created from the prefab.
     */
    mobs::Entity instantiate(const std::string &prefabName, GameContext &gameContext);

    /**
     * @brief Updates the scene manager.
     *
     * @param gameContext The context of the game.
     */
    bool update(GameContext &gameContext);
    void setScenes(const std::map<std::string, std::string> &scenes) { _scenes = scenes; }
    void setPrefabs(const std::map<std::string, std::string> &prefabs) { _prefabs = prefabs; }

   private:
    /**
     * @brief Creates an entity from a prefab JSON.
     *
     * @param prefabJson The JSON data of the prefab.
     * @param entity The entity to create.
     * @param registry The registry containing all entities and components.
     * @param gameContext The context of the game.
     */
    void createEntity(const nlohmann::json &prefabJson, mobs::Entity entity,
                      mobs::Registry &registry, GameContext &gameContext);

    template <typename... T>
    void copyEntity(mobs::Entity from, mobs::Entity to, mobs::Registry &registry) {
        (copyComponents<T>(from, to, registry), ...);
    }

    template <typename T>
    void copyComponents(mobs::Entity from, mobs::Entity to, mobs::Registry &registry) {
        if (_prefabRegistry.hasComponent<T>(from))
            registry.emplace<T>(to, _prefabRegistry.get<T>(from));
    }

    template <typename T>
    void addComponentIfExists(std::string ComponentName, const nlohmann::json &data,
                              mobs::Registry &registry, mobs::Entity entity)
    {
        if (data.contains(ComponentName))
        {
            T component;
            data.at(ComponentName).get_to(component);
            registry.emplace<T>(entity, component);
        }
    }

    template <typename... T>
    void addComponentsToEntity(const nlohmann::json &componentData, mobs::Registry &registry,
                               mobs::Entity entity)
    {
        (addComponentIfExists<T>(T::name, componentData, registry, entity), ...);
    }

    /**
     * @brief Adds scripts to an entity.
     *
     * @param registry The registry containing all entities and components.
     * @param entity The entity to add scripts to.
     * @param componentData The JSON data of the scripts to add.
     */
    void addScriptsToEntity(mobs::Registry &registry, mobs::Entity entity,
                            const nlohmann::json &componentData);

    using CppScriptCreator = std::function<std::shared_ptr<RType::ICppScript>()>;

    std::unordered_map<std::string, CppScriptCreator> _cppScriptCreators;  ///< C++ script creators.

    void initCppScriptCreators();

    mobs::Registry _prefabRegistry;  ///< The registry containing all prefabs.
    std::string _defaultScene;                    ///< The default scene name.
    std::string _currentScene;                    ///< The current scene name.
    std::map<std::string, std::string> _scenes;   ///< The scenes.
    std::map<std::string, std::string> _prefabs;  ///< The prefabs.
};

}  // namespace RType

#endif  // SCENEMANAGER_H