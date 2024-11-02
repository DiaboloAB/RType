/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include "ClientEventType.hpp"
#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"

namespace RType
{

class Menu : public RType::ICppScript
{
   public:
    void start(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
        {
            gameContext.get<Audio>("soundManager").audioQueue.push("sounds/mainTrack.ogg");
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        if (gameContext._sceneManager.getCurrentScene() != "menu") return;
        if (gameContext._runtime->getKeyDown(KeyCode::UpArrow) ||
            gameContext._runtime->getKeyDown(KeyCode::DownArrow) ||
            gameContext._runtime->getKeyDown(KeyCode::LeftArrow) ||
            gameContext._runtime->getKeyDown(KeyCode::RightArrow))
        {
            try
            {
                gameContext.get<Audio>("soundManager").audioQueue.push("sounds/bip.ogg");
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void onButtonPressed(
        mobs::Registry &registry, GameContext &gameContext, std::string action,
        const std::vector<std::variant<mlg::vec3, int, std::string>> &args) override
    {
        if (action == "settings")
            gameContext._sceneManager.switchScene("settings");
        else if (action == "exit")
            gameContext._running = false;
        else if (action == "return")
            gameContext._sceneManager.switchScene("menu");
        else if (action == "fullscreen")
        {
            fullscreen = !fullscreen;
            gameContext._runtime->FullScreenWindow(fullscreen);
            try
            {
                gameContext.get<Button>("fullscreen").text =
                    fullscreen ? "Fullscreen: On" : "Fullscreen: Off";
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (action == "startGame")
        {
            gameContext._sceneManager.switchScene("scene2");
        }
        else if (action == "findGame")
        {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");
            if (networkC.client->_serverEndpoint)
            {
                auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
                event->setClientEvent(dimension::ClientEventType::ROOM);
                event->setDescription("join=rd");
                networkC.client->send(event, *networkC.client->getDirectionEndpoint());
            }
        }
        else if (action == "hostGame")
        {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");
            if (networkC.client->_serverEndpoint)
            {
                auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
                event->setClientEvent(dimension::ClientEventType::ROOM);
                event->setDescription("create=pv");
                networkC.client->send(event, *networkC.client->getDirectionEndpoint());
            }
        }
        else if (action == "connect")
        {
            mobs::Registry::View viewClient = registry.view<NetworkClient>();
            auto &networkC = registry.get<NetworkClient>(viewClient.front());
            std::string host = gameContext.get<Button>("hostInput").content;
            unsigned int port =
                static_cast<unsigned int>(std::stoul(gameContext.get<Button>("portInput").content));
            gameContext.get<Text>("status").text = "status: connected";
            gameContext.get<Text>("status").color = mlg::vec3(0, 255, 0);
            networkC.client->connectServer(host, port);
        }
        else if (action == "joinPrivate")
        {
            auto &networkC = gameContext.get<NetworkClient>("NetworkCom");
            if (networkC.client->_serverEndpoint)
            {
                std::string code = gameContext.get<Button>("Game Code").content;
                auto event = networkC.factory.createEmptyPacket<dimension::ClientEvent>();
                event->setClientEvent(dimension::ClientEventType::ROOM);
                event->setDescription("join=" + code);
                networkC.client->send(event, *networkC.client->getDirectionEndpoint());
            }
        }
    }

    static constexpr const char *name = "Menu";

   private:
    bool fullscreen = false;
    int _eventID = 0;
};

}  // namespace RType

#endif  // MENU_HPP