/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/components.hpp"
#include "common/cppScripts/AnimPlayer.hpp"
#include "common/cppScripts/AnimThruster.hpp"
#include "common/cppScripts/EnemyFactory.hpp"
#include "common/cppScripts/Laser.hpp"
#include "common/cppScripts/MovePlayer.hpp"
#include "common/cppScripts/MoveThruster.hpp"
#include "common/cppScripts/PlayerShoot.hpp"
#include "common/cppScripts/RedShipScript.hpp"
#include "common/cppScripts/helloworld.hpp"
#include "common/scriptsComponent.hpp"

using namespace RType;

void SceneManager::addScriptsToEntity(mobs::Registry &registry, mobs::Entity entity,
                                      const nlohmann::json &componentData)
{
    try
    {
        registry.emplace<CppScriptComponent>(entity, entity);
        auto &scripts = registry.get<CppScriptComponent>(entity);
        for (const auto &script : componentData)
        {
            auto it = _cppScriptCreators.find(script.get<std::string>());
            if (it != _cppScriptCreators.end())
            {
                scripts.addScript(it->second());
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: Could not create script" << std::endl;
        throw std::runtime_error("Could not create script");
    }
}