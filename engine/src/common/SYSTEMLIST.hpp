/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SYSTEMLIST_H
#define SYSTEMLIST_H

#include "common/network/systems/roomSystem.hpp"
#include "common/systems/AudioSystem.hpp"
#include "common/systems/CppScriptsSystem.hpp"
#include "common/systems/DrawableSystem.hpp"
#include "common/systems/PhysicsCollisionSystem.hpp"
#include "common/systems/ScriptsSystem.hpp"
#include "common/systems/SpriteSystem.hpp"
#include "common/systems/StickySystem.hpp"
#include "common/systems/AdminSystem.hpp"

#define SYSTEM_TYPES                                                                     \
    ScriptSystem, SpriteSystem, CppScriptsSystem, AudioSystem, StickySystem, RoomSystem, \
        PhysicsSystem, DrawableSystem, AudioSystem, AdminSystem

#endif  // SYSTEMLIST_H