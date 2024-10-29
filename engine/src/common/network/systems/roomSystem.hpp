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

    void start(mobs::Registry &registry, GameContext &gameContext)
    {
        try
        {
            std::map<std::string, std::string> args = gameContext._args;
            if (args.find("host") != args.end() && args.find("port") != args.end() &&
                args.find("code") != args.end())
            {
                auto entity = registry.create();
                registry.emplace<Basics>(entity, "room", "", false);
                registry.emplace<NetworkRoom>(
                    entity, args.at("host"), static_cast<unsigned int>(std::stoul(args.at("port"))),
                    args.at("code"));
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
