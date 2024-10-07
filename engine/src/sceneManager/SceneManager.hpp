/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

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

    void update(GameContext &gameContext);

    std::string _nextScene = "";

   private:
    std::string _defaultScene;
    std::string _currentScene;
    std::vector<std::string> _scenesList;
};

}  // namespace RType

#endif  // SCENEMANAGER_H