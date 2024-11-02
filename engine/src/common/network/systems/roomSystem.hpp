/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <system/ISystem.hpp>
// std

namespace RType
{
class RoomSystem : public ISystem
{
   public:
    RoomSystem() {}
    ~RoomSystem() {}

    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        try
        {
            std::map<std::string, std::string> args = gameContext._args;
            if (args.find("host") != args.end() && args.find("port") != args.end() &&
                args.find("code") != args.end())
            {
                mobs::Entity entity = gameContext._sceneManager.instantiate("room", gameContext);
                auto &room = registry.get<NetworkRoom>(entity);
                room.room = std::make_shared<dimension::Room>(
                    std::make_shared<dimension::PacketFactory>(), args.at("host"),
                    static_cast<unsigned int>(std::stoul(args.at("port"))), args.at("code"));
            }
        }
        catch (std::exception &e)
        {
            ERR_LOG("RoomSystem", std::string("Something went wrong {") + e.what() + "}");
        }
    }

   private:
};
}  // namespace RType
