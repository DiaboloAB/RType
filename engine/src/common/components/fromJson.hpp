#ifndef FROMJSON_HPP
#define FROMJSON_HPP

#include <mlg/mlg.hpp>
#include <nlohmann/json.hpp>

#include "components.hpp"
#include "scriptsComponent.hpp"

namespace mlg
{
void from_json(const nlohmann::json& j, vec3& v)
{
    if (j.is_array() && j.size() == 3)
    {
        v.x = j.at(0).get<float>();
        v.y = j.at(1).get<float>();
        v.z = j.at(2).get<float>();
    }
    else if (j.is_object())
    {
        j.at("x").get_to(v.x);
        j.at("y").get_to(v.y);
        j.at("z").get_to(v.z);
    }
    else
    {
        throw std::runtime_error("Invalid JSON format for vec3");
    }
}
}  // namespace mlg

namespace RType
{
void from_json(const nlohmann::json& j, Transform& transform)
{
    if (j.contains("position")) j.at("position").get_to(transform.position);
    if (j.contains("rotation")) j.at("rotation").get_to(transform.rotation);
    if (j.contains("scale")) j.at("scale").get_to(transform.scale);
}

void from_json(const nlohmann::json& j, RigidBody& RigidBody)
{
    if (j.contains("mass")) j.at("mass").get_to(RigidBody.mass);
    if (j.contains("restitution")) j.at("restitution").get_to(RigidBody.restitution);
    if (j.contains("Physic")) j.at("Physic").get_to(RigidBody.Physic);
}

void from_json(const nlohmann::json& j, Sprite& sprite)
{
    if (!j.contains("texture")) throw std::runtime_error("Sprite must have a texture file path");
    j.at("texture").get_to(sprite.filePath);
}

void from_json(const nlohmann::json& j, Animation& animation)
{
    if (!j.contains("name")) throw std::runtime_error("Animation must have a name");
    j.at("name").get_to(animation.name);

    if (!j.contains("speed")) throw std::runtime_error("Animation must have a speed");
    j.at("speed").get_to(animation.speed);

    if (!j.contains("texture")) throw std::runtime_error("Animation must have a texture file path");
    j.at("texture").get_to(animation.filepath);

    if (!j.contains("frameCount")) throw std::runtime_error("Animation must have a frame count");
    j.at("frameCount").get_to(animation.frameCount);

    if (!j.contains("frameSize")) throw std::runtime_error("Animation must have a frame size");
    j.at("frameSize").get_to(animation.frameSize);

    if (j.contains("loop")) j.at("loop").get_to(animation.loop);
}

void from_json(const nlohmann::json& j, Animator& animator)
{
    if (j.contains("animations"))
    {
        for (const auto& anim_json : j.at("animations"))
        {
            Animation animation;
            from_json(anim_json, animation);
            animator.animations.addAnimation(animation);
        }
    }
}

void from_json(const nlohmann::json& j, Event& event)
{
    if (j.contains("prefab")) j.at("prefab").get_to(event.prefab);

    if (j.contains("position")) j.at("position").get_to(event.position);

    if (!j.contains("delay")) throw std::runtime_error("event must have a delay");
    j.at("delay").get_to(event.delay);

    if (!j.contains("type")) throw std::runtime_error("event must have a type");
    j.at("type").get_to(event.type);

    if (j.contains("scale")) j.at("scale").get_to(event.scale);
}

void from_json(const nlohmann::json& j, EventManager& eventManager)
{
    if (j.contains("eventList"))
    {
        for (const auto& event_json : j.at("eventList"))
        {
            Event event;
            from_json(event_json, event);
            eventManager.eventList.push_back(event);
        }
    }
}

void from_json(const nlohmann::json& j, Sticky& sticky)
{
    if (!j.contains("target")) throw std::runtime_error("Sticky must have a target");
    j.at("target").get_to(sticky.target);

    if (j.contains("offset")) j.at("offset").get_to(sticky.offset);
}

void from_json(const nlohmann::json& j, Collider& collider)
{
    if (!j.contains("size")) throw std::runtime_error("Collider must have a size");
    j.at("size").get_to(collider.size);
    if (j.contains("offset")) j.at("offset").get_to(collider.offset);

    if (j.contains("isTrigger")) j.at("isTrigger").get_to(collider.isTrigger);

    if (j.contains("layerMask"))
    {
        for (const auto& layer : j.at("layerMask"))
        {
            collider.layerMask.push_back(layer);
        }
    }
}

void from_json(const nlohmann::json& j, Audio& audio)
{
    if (j.contains("musicList"))
    {
        for (const auto& music : j.at("musicList"))
        {
            audio.musicList[music] = -1;
        }
    }
    if (j.contains("soundList"))
    {
        for (const auto& sound : j.at("soundList"))
        {
            audio.soundList[sound] = -1;
        }
    }
    if (j.contains("musicVolume")) j.at("musicVolume").get_to(audio.musicVolume);
    if (j.contains("soundVolume")) j.at("soundVolume").get_to(audio.soundVolume);
}

}  // namespace RType

#endif  // FROMJSON_HPP