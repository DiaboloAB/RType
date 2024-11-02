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
    void load(mobs::Registry &registry, GameContext &gameContext) override
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
            gameContext._runtime->FullScreenWindow();
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
            mobs::Registry::View view = registry.view<NetworkClient>();
            auto &networkC = registry.get<NetworkClient>(view.front());
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
            mobs::Registry::View view = registry.view<NetworkClient>();
            auto &networkC = registry.get<NetworkClient>(view.front());
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
            std::string host = "127.0.0.1";
            unsigned int port = 8581;
            mobs::Registry::View viewClient = registry.view<NetworkClient>();
            auto &networkC = registry.get<NetworkClient>(viewClient.front());
            mobs::Registry::View viewBasics = registry.view<Basics>();
            for (auto &entity : viewBasics) {
                auto &basics = registry.get<Basics>(entity);
                if (basics.tag == "hostInput") {
                    auto &button = registry.get<Button>(entity);
                    host = button.content;
                }
                if (basics.tag == "portInput") {
                    auto &button = registry.get<Button>(entity);
                    port = static_cast<unsigned int>(std::stoul(button.content));
                }
            }
            networkC.client->connectServer(host, port);
        }
    }

    static constexpr const char *name = "Menu";

   private:
    bool fullscreen = false;
    int _eventID = 0;
};

}  // namespace RType

#endif  // MENU_HPP