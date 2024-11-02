/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTSCOMPONENT_H
#define SCRIPTSCOMPONENT_H

#include <mlg/mlg.hpp>

#include "common/ICppScript.hpp"
#include "gameContext/GameContext.hpp"
#include "lua/luaBindings.hpp"
#include "mobs/mobs.hpp"
// std
#include <utility>

namespace RType
{

struct Scripts
{
    std::vector<std::string> scripts;
    std::vector<lua_State*> luaStates;
    mobs::Entity entity;

    void startAll(mobs::Registry& registry, GameContext& gameContext)
    {
        for (auto L : luaStates)
        {
            lua_getglobal(L, "start");

            lua_pushlightuserdata(L, &registry);
            lua_pushlightuserdata(L, &gameContext);

            if (lua_pcall(L, 2, 0, 0) != LUA_OK)
            {
                std::cerr << "Failed to call start: " << lua_tostring(L, -1) << std::endl;
                lua_pop(L, 1);
            }
        }
    }

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

    void onCollisionStayAll(mobs::Registry& registry, GameContext& gameContext, mobs::Entity other)
    {
        for (auto& script : scripts)
        {
            script->onCollisionStay(registry, gameContext, other);
        }
    }

    void onCollisionEnterAll(mobs::Registry& registry, GameContext& gameContext, mobs::Entity other)
    {
        for (auto& script : scripts)
        {
            script->onCollisionEnter(registry, gameContext, other);
        }
    }

    void onCollisionExitAll(mobs::Registry& registry, GameContext& gameContext, mobs::Entity other)
    {
        for (auto& script : scripts)
        {
            script->onCollisionExit(registry, gameContext, other);
        }
    }

    void onButtonPressedAll(mobs::Registry& registry, GameContext& gameContext, std::string action,
                            const std::vector<std::variant<mlg::vec3, int, std::string>>& args)
    {
        for (auto& script : scripts)
        {
            try
            {
                script->onButtonPressed(registry, gameContext, action, args);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }

    void addScript(std::shared_ptr<ICppScript> script)
    {
        script->setEntity(entity);
        scripts.push_back(std::move(script));
    }

    template <typename T>
    std::shared_ptr<T> getScript()
    {
        for (auto& script : scripts)
        {
            if (auto casted = std::dynamic_pointer_cast<T>(script))
            {
                return casted;
            }
        }
        return nullptr;
    }

    CppScriptComponent(mobs::Entity entity) : entity(entity) {}
};

}  // namespace RType

#endif  // SCRIPTSCOMPONENT_H