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
     * @brief Constructs a new SceneManager object.
     */
    SceneManager();

    /**
     * @brief Destroys the SceneManager object.
     */
    ~SceneManager();

    void switchScene(const std::string &sceneName) { _nextScene = sceneName; }

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

    /**
     * @brief Gets the current scene name.
     *
     * @return std::string The current scene name.
     */
    std::string getCurrentScene() const { return _currentScene; }

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

    /**
     * @brief The name of the next scene to load.
     */
    std::string _nextScene = "";
    bool _prefabLoaded = false;

    std::string _defaultScene;                    ///< The default scene name.
    std::string _currentScene;                    ///< The current scene name.
    std::map<std::string, std::string> _scenes;   ///< The scenes.
    std::map<std::string, std::string> _prefabs;  ///< The prefabs.
};

}  // namespace RType

#endif  // SCENEMANAGER_H