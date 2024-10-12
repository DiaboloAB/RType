/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "SceneManager.hpp"
#include "common/components.hpp"
#include "common/scriptsComponent.hpp"
#include "gameContext/GameContext.hpp"

using namespace RType;

void SceneManager::initComponentCreators()
{
    _componentCreators["Transform"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    {
        registry.emplace<Transform>(
            entity, mlg::vec3(componentData["position"][0], componentData["position"][1],
                              componentData["position"][2]));
    };
    _componentCreators["Sprite"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    { registry.emplace<Sprite>(entity, componentData["texture"].get<std::string>()); };
    _componentCreators["Network"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    {
        registry.emplace<NetworkComp>(entity, componentData["id"],
                                      componentData["authority"].get<std::string>());
    };
    _componentCreators["Timer"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    { registry.emplace<CoolDown>(entity, componentData["active"].get<bool>()); };
    _componentCreators["Hitbox"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    {
        registry.emplace<Hitbox>(
            entity, mlg::vec3(componentData["size"][0], componentData["size"][1], 0),
            mlg::vec3(componentData["offSet"][0], componentData["offSet"][1], 0),
            componentData["isEnemy"].get<bool>());
    };
    _componentCreators["Animator"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    {
        registry.emplace<Animator>(entity);
        auto &animator = registry.get<Animator>(entity);
        for (const auto &animation : componentData)
        {
            animator.animations.addAnimation(
                Animation(animation["texture"].get<std::string>(),
                          animation["frameCount"].get<int>(), animation["speed"].get<float>(),
                          mlg::vec3(animation["frameSize"][0], animation["frameSize"][1], 0),
                          mlg::vec3(animation["scale"][0], animation["scale"][1], 0),
                          animation["rotation"].get<float>(), animation["name"].get<std::string>(),
                          animation["loop"].get<bool>()));
        }
    };
    _componentCreators["Health"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    { registry.emplace<Health>(entity, componentData["health"].get<int>()); };
    _componentCreators["Ally"] =
        [](mobs::Registry &registry, mobs::Entity entity, const nlohmann::json &componentData)
    { registry.emplace<Ally>(entity); };
}