#ifndef FROMJSON_HPP
#define FROMJSON_HPP

#include <nlohmann/json.hpp>
#include "components.hpp"

namespace RType
{
    void from_json(const nlohmann::json& j, Transform& transform)
    {
        // j.at("position").get_to(transform.position);
        // j.at("rotation").get_to(transform.rotation);
        // j.at("scale").get_to(transform.scale);
    }
}

#endif // FROMJSON_HPP