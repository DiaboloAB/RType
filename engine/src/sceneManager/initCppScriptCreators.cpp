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

void SceneManager::initCppScriptCreators()
{
    _cppScriptCreators["HelloWorld"] = []() { return std::make_shared<HelloWorldScript>(); };
    _cppScriptCreators["MovePlayer"] = []() { return std::make_shared<MovePlayerScript>(); };
    _cppScriptCreators["AnimPlayer"] = []() { return std::make_shared<AnimPlayerScript>(); };
    _cppScriptCreators["AnimThruster"] = []() { return std::make_shared<AnimThrusterScript>(); };
    _cppScriptCreators["EnemyFactory"] = []() { return std::make_shared<EnemyFactoryScript>(); };
    _cppScriptCreators["RedShip"] = []() { return std::make_shared<RedShipScript>(); };
    _cppScriptCreators["PlayerShoot"] = []() { return std::make_shared<PlayerShootScript>(); };
    _cppScriptCreators["Laser"] = []() { return std::make_shared<LaserScript>(); };
    _cppScriptCreators["MoveThruster"] = []() { return std::make_shared<MoveThrusterScript>(); };
}
