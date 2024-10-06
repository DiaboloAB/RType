/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "gameContext/GameContext.hpp"
#include "mobs/mobs.hpp"
#include <mlg/mlg.hpp>
#include <lua.hpp>
// std
#include <vector>
#include <string>
#include <iostream>

namespace RType
{
struct Transform
{
    mlg::vec3 position;
    mlg::vec3 rotation;
    mlg::vec3 scale;

    Transform(mlg::vec3 position, mlg::vec3 rotation, mlg::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform(mlg::vec3 position) : position(position), rotation(mlg::vec3(0.0f)), scale(mlg::vec3(1.0f)) {}
    Transform() : position(mlg::vec3(0.0f)), rotation(mlg::vec3(0.0f)), scale(mlg::vec3(1.0f)) {}
};

struct Velocity
{
    mlg::vec3 velocity;

    Velocity(mlg::vec3 velocity) : velocity(velocity) {}
};

struct Sprite
{
    std::string filePath;

    Sprite(std::string filePath) : filePath(filePath) {}
};

struct Scripts
{
    std::vector<std::string> scripts;
    std::vector<lua_State*> luaStates;

    void addScript(const std::string& scriptFile) {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        if (luaL_dofile(L, (std::string("assets/scripts/") + scriptFile).c_str()) != LUA_OK) {
            std::cerr << "Failed to load Lua script: " << lua_tostring(L, -1) << std::endl;
        } else {
            std::cout << "Loaded Lua script: " << scriptFile << std::endl;
            scripts.push_back(scriptFile);
            luaStates.push_back(L);
        }
    }

    void updateAll(mobs::Registry& registry, GameContext& gameContext) {
        for (auto L : luaStates) {
            lua_getglobal(L, "update");

            lua_pushlightuserdata(L, &registry);
            lua_pushlightuserdata(L, &gameContext);

            if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
                std::cerr << "Failed to call update: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }
    }

    ~Scripts() {
        for (auto L : luaStates) {
            lua_close(L);
        }
    }
};


}  // namespace RType

#endif  // COMPONENTS_H