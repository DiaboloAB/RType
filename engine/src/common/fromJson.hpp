#ifndef FROMJSON_HPP
#define FROMJSON_HPP

#include <nlohmann/json.hpp>
#include "components.hpp"
#include "scriptsComponent.hpp"
#include <mlg/mlg.hpp>

namespace mlg {
    void from_json(const nlohmann::json& j, vec3& v)
    {
        if (j.is_array() && j.size() == 3) {
            v.x = j.at(0).get<float>();
            v.y = j.at(1).get<float>();
            v.z = j.at(2).get<float>();
        } else if (j.is_object()) {
            j.at("x").get_to(v.x);
            j.at("y").get_to(v.y);
            j.at("z").get_to(v.z);
        } else {
            throw std::runtime_error("Invalid JSON format for vec3");
        }
    }
}

namespace RType
{
    void from_json(const nlohmann::json& j, Transform& transform)
    {
        if (j.contains("position"))
        j.at("position").get_to(transform.position);
        if (j.contains("rotation"))
            j.at("rotation").get_to(transform.rotation);
        if (j.contains("scale"))
            j.at("scale").get_to(transform.scale);
    }

    void from_json(const nlohmann::json& j, Sprite& sprite)
    {
        if (!j.contains("texture"))
            throw std::runtime_error("Sprite must have a texture file path");
        j.at("texture").get_to(sprite.filePath);
    }
}

#endif // FROMJSON_HPP