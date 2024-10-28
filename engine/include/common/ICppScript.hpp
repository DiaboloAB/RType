/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ICPPSCRIPT_H
#define ICPPSCRIPT_H

#include <memory>
#include <vector>

#include "mobs/mobs.hpp"
// std
#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <memory>

namespace RType
{
class GameContext;

/**
 * @class ICppScript
 * @brief Interface for C++ scripts used in the RType game engine.
 */
class ICppScript
{
   public:
    /**
     * @brief Virtual destructor for ICppScript.
     */
    virtual ~ICppScript() = default;

    /**
     * @brief Called when the script starts.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void start(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called every frame to update the script.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void update(mobs::Registry &registry, GameContext &gameContext) {}

    /**
     * @brief Called when a collision occurs.
     *
     * @param registry Reference to the entity-component registry.
     * @param gameContext Reference to the game context.
     */
    virtual void onCollision(mobs::Registry &registry, GameContext &gameContext, mobs::Entity other) {}

   template <typename Func>
    void registerFunction(const std::string &functionName, Func function)
    {
        functions[functionName] = std::make_any<Func>(function);
    }

    template <typename... Args>
    void callFunction(const std::string &functionName, mobs::Registry &registry, GameContext &gameContext, Args... args)
    {
        if (functions.find(functionName) != functions.end())
        {
            try {
                auto func = std::any_cast<std::function<void(mobs::Registry&, GameContext&, Args...)>>(functions[functionName]);
                func(registry, gameContext, args...);
            } catch (const std::bad_any_cast&) {
                std::cerr << "Error: Argument types do not match for function " << functionName << "." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Function " << functionName << " not found." << std::endl;
        }
    }

     /**
     * @brief Sets the entity associated with this script.
     *
     * @param entity The entity to associate with this script.
     */
    virtual void setEntity(mobs::Entity entity) = 0;

   private:
    std::map<std::string, std::any> functions;
};

}  // namespace RType

#endif  // ICPPSCRIPT_H