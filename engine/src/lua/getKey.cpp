/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GETKEY_H
#define GETKEY_H

#include "LuaBindings.hpp"


RType::KeyCode stringToKeyCode(const std::string& keyName)
{
    static std::unordered_map<std::string, RType::KeyCode> keyMap = {
        {"A", RType::KeyCode::A},
        {"B", RType::KeyCode::B},
        {"C", RType::KeyCode::C},
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
    RType::GameContext* gameContext = static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    bool isPressed = gameContext->_runtime->getKey(keyCode);

    lua_pushboolean(L, isPressed);

    return 1;
}

int getKeyDown(lua_State* L)
{
    const char* keyName = lua_tostring(L, 1);

    RType::KeyCode keyCode = stringToKeyCode(std::string(keyName));
    RType::GameContext* gameContext = static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    bool isPressed = gameContext->_runtime->getKeyDown(keyCode);

    lua_pushboolean(L, isPressed);

    return 1;
}

int getKeyUp(lua_State* L)
{
    const char* keyName = lua_tostring(L, 1);

    RType::KeyCode keyCode = stringToKeyCode(std::string(keyName));
    RType::GameContext* gameContext = static_cast<RType::GameContext*>(lua_touserdata(L, lua_upvalueindex(1)));

    bool isPressed = gameContext->_runtime->getKeyUp(keyCode);

    lua_pushboolean(L, isPressed);

    return 1;
}

void initializeLuaBindings(lua_State* L, RType::GameContext* gameContext)
{
    lua_pushlightuserdata(L, gameContext);

    lua_pushcclosure(L, (lua_CFunction)getKey, 1);
    lua_setglobal(L, "getKey");

    // lua_pushcclosure(L, (lua_CFunction)getKeyDown, 1);
    // lua_setglobal(L, "getKeyDown");

    // lua_pushcclosure(L, (lua_CFunction)getKeyUp, 1);
    // lua_setglobal(L, "getKeyUp");
}


#endif // GETKEY_H