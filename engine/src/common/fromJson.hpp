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

    if (j.contains("scale")) j.at("scale").get_to(animation.scale);
    if (j.contains("rotation")) j.at("rotation").get_to(animation.rotation);
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

}  // namespace RType

#endif  // FROMJSON_HPP