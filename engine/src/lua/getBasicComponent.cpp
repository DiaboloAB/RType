/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "luaBindings.hpp"
#include "common/components/components.hpp"

#include "luaBindings.hpp"

int getLuaGlobalInteger(lua_State* L, const char* name)
{
    lua_getglobal(L, name);
    if (!lua_isinteger(L, -1))
    {
        lua_pop(L, 1);
        throw std::runtime_error("Global variable is not an integer");
    }
    int value = lua_tointeger(L, -1);
    lua_pop(L, 1);
    return value;
}

int getPosition(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    int entityId = getLuaGlobalInteger(L, "entityId");

    if (gameContext->_registry.hasComponent<RType::Transform>(entityId)) {
        RType::Transform &transform = gameContext->_registry.get<RType::Transform>(entityId);
        lua_pushnumber(L, transform.position.x);
        lua_pushnumber(L, transform.position.y);
        return 2;
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        return 2;
    }
}

void setPosition(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    int entityId = getLuaGlobalInteger(L, "entityId");

    if (gameContext->_registry.hasComponent<RType::Transform>(entityId)) {
        RType::Transform &transform = gameContext->_registry.get<RType::Transform>(entityId);
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        transform.position.x = x;
        transform.position.y = y;
    }
}

int getRigidBody(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    int entityId = getLuaGlobalInteger(L, "entityId");
    if (gameContext->_registry.hasComponent<RType::RigidBody>(entityId)) {
        RType::RigidBody &rigidBody = gameContext->_registry.get<RType::RigidBody>(entityId);
        lua_pushnumber(L, rigidBody.velocity.x);
        lua_pushnumber(L, rigidBody.velocity.y);
        return 2;
    } else {
        lua_pushnumber(L, 0);
        lua_pushnumber(L, 0);
        return 2;
    }
    
}

void setRigidBody(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    int entityId = getLuaGlobalInteger(L, "entityId");
    if (gameContext->_registry.hasComponent<RType::RigidBody>(entityId)) {
        RType::RigidBody &rigidBody = gameContext->_registry.get<RType::RigidBody>(entityId);
        rigidBody.velocity.x = luaL_checknumber(L, 1);
        rigidBody.velocity.y = luaL_checknumber(L, 2);
    }
}