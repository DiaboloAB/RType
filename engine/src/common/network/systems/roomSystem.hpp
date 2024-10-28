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

    void start(mobs::Registry &registry, GameContext &gameContext) {
        /**Condition si vaarg contient host port code */
        if (true) {
            auto entity = registry.create();
            registry.emplace<Basics>(entity, "room", "", false);
            registry.emplace<NetworkRoom>(entity, /*host*/, /*port*/, /*code*/);
        }
    }

   private:
};
}  // namespace RType
