/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef LUABINDINGS_H
#define LUABINDINGS_H

#include <lua.hpp>

#include "gameContext/GameContext.hpp"

void initializeLuaBindings(lua_State* L, RType::GameContext* gameContext);

void playMusicSound(lua_State* L);


#endif  // LUABINDINGS_H