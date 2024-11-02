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

int getLuaGlobalInteger(lua_State* L, const char* name);


void playMusicSound(lua_State* L);
int getPosition(lua_State* L);
void setPosition(lua_State* L);
void setRigidBody(lua_State* L);
int getRigidBody(lua_State* L);



#endif  // LUABINDINGS_H