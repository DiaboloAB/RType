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
// std

RType::KeyCode stringToKeyCode(const std::string& keyName);

int getKey(lua_State* L);
int getKeyDown(lua_State* L);
int getKeyUp(lua_State* L);

void initializeLuaBindings(lua_State* L, RType::GameContext* gameContext);

#endif  // LUABINDINGS_H