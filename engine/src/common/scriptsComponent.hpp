/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTSCOMPONENT_H
#define SCRIPTSCOMPONENT_H

#include <lua.hpp>
#include <mlg/mlg.hpp>

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "lua/LuaBindings.hpp"
#include "mobs/mobs.hpp"
// std

namespace RType
{

struct Scripts
{
    std::vector<std::string> scripts;
    std::vector<lua_State*> luaStates;
    mobs::Entity entity;

    void add(const std::string& scriptFile, GameContext& gameContext)
    {
        lua_State* L = luaL_newstate();
        luaL_openlibs(L);
        if (luaL_dofile(L, scriptFile.c_str()) != LUA_OK)
        {
            std::cerr << "Failed to load Lua script: " << lua_tostring(L, -1) << std::endl;
        }
        else
        {
            initializeLuaBindings(L, &gameContext);

            scripts.push_back(scriptFile);
            luaStates.push_back(L);
        }
    }

    void updateAll(mobs::Registry& registry, GameContext& gameContext)
    {
        for (auto L : luaStates)
        {
            lua_getglobal(L, "update");

            lua_pushlightuserdata(L, &registry);
            lua_pushlightuserdata(L, &gameContext);

            if (lua_pcall(L, 2, 0, 0) != LUA_OK)
            {
                std::cerr << "Failed to call update: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }
    }

    Scripts(mobs::Entity entity) : entity(entity) {}

    ~Scripts()
    {
        for (auto L : luaStates)
        {
            lua_close(L);
        }
    }
};

struct CppScriptComponent
{
    std::vector<std::shared_ptr<ICppScript>> scripts;
    mobs::Entity entity;

    void startAll(mobs::Registry& registry, GameContext& gameContext)
    {
        for (auto& script : scripts)
        {
            script->start(registry, gameContext);
        }
    }

    void updateAll(mobs::Registry& registry, GameContext& gameContext)
    {
        for (auto& script : scripts)
        {
            try
            {
                script->update(registry, gameContext);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    void onCollisionAll(mobs::Registry& registry, GameContext& gameContext, mobs::Entity other)
    {
        for (auto& script : scripts)
        {
            script->onCollision(registry, gameContext, other);
        }
    }

    void addScript(std::shared_ptr<ICppScript> script)
    {
        script->setEntity(entity);
        scripts.push_back(std::move(script));
    }

    void callAllFunctions(const std::string& functionName, mobs::Registry& registry,
                          GameContext& gameContext)
    {
        // for (auto& script : scripts)
        // {
        //     script->callFunction(functionName, registry, gameContext);
        // }
    }

    CppScriptComponent(mobs::Entity entity) : entity(entity) {}
};

}  // namespace RType

#endif  // SCRIPTSCOMPONENT_H