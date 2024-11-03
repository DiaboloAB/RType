#ifndef ADMINFROMJSON_HPP
#define ADMINFROMJSON_HPP

#include <mlg/mlg.hpp>
#include <nlohmann/json.hpp>

#include "components.hpp"
#include "adminComponents.hpp"

namespace RType
{
void from_json(const nlohmann::json& j, Console& console)
{
    if (j.contains("fontPath"))
        console.fontPath = j.at("fontPath").get<std::string>();
    if (j.contains("fontSize"))
        console.fontSize = j.at("fontSize").get<float>();
}

void from_json(const nlohmann::json& j, Metrics& metrics)
{
    if (j.contains("fontPath"))
        metrics.fontPath = j.at("fontPath").get<std::string>();
    if (j.contains("fontSize"))
        metrics.fontSize = j.at("fontSize").get<float>();
}

}  // namespace RType

#endif  // FROMJSON_HPP