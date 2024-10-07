/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include <IRuntime/IRuntime.hpp>
#include <RenderSystemSFML/RenderSystemSFML.hpp>
#include <mobs/mobs.hpp>
#include <sceneManager/SceneManager.hpp>
#include <NetworkHandler/NetworkHandler.hpp>
#include <chrono>

namespace RType
{

class GameContext
{
   public:
    GameContext(mobs::Registry &registry, SceneManager &sceneManager);
    ~GameContext();

    void update()
    {
        std::chrono::high_resolution_clock::time_point newTime =
            std::chrono::high_resolution_clock::now();
        _deltaT = std::chrono::duration<float, std::chrono::seconds::period>(newTime - _currentTime)
                      .count();
        _currentTime = newTime;
        _sceneManager.update(*this);
    }

    void setNetworkHandler(std::shared_ptr<Network::NetworkHandler> newNetworkHandler)
    {
        this->_networkHandler = newNetworkHandler;
    }

    float _deltaT;
    IRuntime *_runtime;
    mobs::Registry &_registry;
    SceneManager &_sceneManager;
    std::shared_ptr<Network::NetworkHandler> _networkHandler;

   private:
    std::chrono::high_resolution_clock::time_point _currentTime;
};

}  // namespace RType

#endif  // GAMECONTEXT_H