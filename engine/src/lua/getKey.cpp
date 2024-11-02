/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GETKEY_H
#define GETKEY_H

#include "luaBindings.hpp"

RType::KeyCode stringToKeyCode(const std::string& keyName)
{
    static std::unordered_map<std::string, RType::KeyCode> keyMap = {
        {"Enter", RType::KeyCode::Enter},
        {"Space", RType::KeyCode::Space},
        {"UpArrow", RType::KeyCode::UpArrow},
        {"DownArrow", RType::KeyCode::DownArrow},
        {"LeftArrow", RType::KeyCode::LeftArrow},
        {"RightArrow", RType::KeyCode::RightArrow},
        {"Escape", RType::KeyCode::Escape},
    };

    auto it = keyMap.find(keyName);
    if (it != keyMap.end())
    {
        return it->second;
    }
    return RType::KeyCode::None;
}

int getKey(lua_State* L)
{
    const char* keyName = lua_tostring(L, 1);

    RType::KeyCode keyCode = stringToKeyCode(std::string(keyName));
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    bool isPressed = gameContext->_runtime->getKey(keyCode);

    lua_pushboolean(L, isPressed);

    return 1;
}

int getKeyDown(lua_State* L)
{
    if (lua_gettop(L) < 1)
    {
        lua_pushboolean(L, false);
        return 1;
    }

    const char* key = lua_tostring(L, 1);
    if (key == nullptr)
    {
        lua_pushboolean(L, false);
        return 1;
    }

    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));
    if (gameContext == nullptr)
    {
        lua_pushboolean(L, false);
        return 1;
    }
    RType::KeyCode keyCode = stringToKeyCode(std::string(key));

    bool isKeyDown = gameContext->_runtime->getKeyDown(keyCode);

    lua_pushboolean(L, isKeyDown);
    return 1;
}

int getKeyUp(lua_State* L)
{
    const char* keyName = lua_tostring(L, 1);

    RType::KeyCode keyCode = stringToKeyCode(std::string(keyName));
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    bool isPressed = gameContext->_runtime->getKeyUp(keyCode);

    lua_pushboolean(L, isPressed);

    return 1;
}

void exitGame(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    gameContext->_running = false;
}

void switchScene(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    const char* scene = lua_tostring(L, 1);
    gameContext->_sceneManager.switchScene(std::string(scene));
}

void getMousePosition(lua_State* L)
{
    RType::GameContext* gameContext =
        static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    auto pos = gameContext->_runtime->getMousePosition();

    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
}

void initializeLuaBindings(lua_State* L, RType::GameContext* gameContext)
{
    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)getKey, 1);
    lua_setglobal(L, "getKey");

    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)getKeyDown, 1);
    lua_setglobal(L, "getKeyDown");

    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)playMusicSound, 1);
    lua_setglobal(L, "playMusicSound");

    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)exitGame, 1);
    lua_setglobal(L, "exitGame");

    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)switchScene, 1);
    lua_setglobal(L, "switchScene");

    lua_pushlightuserdata(L, gameContext);
    lua_pushcclosure(L, (lua_CFunction)getMousePosition, 1);
    lua_setglobal(L, "getMousePosition");
}

#endif  // GETKEY_H