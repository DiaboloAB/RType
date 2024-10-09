/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <nlohmann/json.hpp>

#include "mobs/mobs.hpp"

// std
#include <functional>
#include <string>
#include <vector>

namespace RType
{

class GameContext;

class SceneManager
{
   public:
    SceneManager();
    ~SceneManager();

    void loadScene(const std::string &sceneName, GameContext &gameContext);
    mobs::Entity loadPrefab(const std::string &prefabName, GameContext &gameContext);

    void update(GameContext &gameContext);

    std::string _nextScene = "";

   private:
    void createEntity(const nlohmann::json &prefabJson, mobs::Entity entity,
                      mobs::Registry &registry, GameContext &gameContext);
    std::string _defaultScene;
    std::string _currentScene;
    std::vector<std::string> _scenesList;

    std::vector<std::string> _prefabsList;
};

}  // namespace RType

#endif  // SCENEMANAGER_H