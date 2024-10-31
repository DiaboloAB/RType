#ifndef UIFROMJSON_HPP
#define UIFROMJSON_HPP

#include <mlg/mlg.hpp>
#include <nlohmann/json.hpp>

#include "components.hpp"
#include "scriptsComponent.hpp"
#include "uiComponents.hpp"

namespace RType
{
void from_json(const nlohmann::json& j, Text& text)
{
    if (j.contains("text")) j.at("text").get_to(text.text);
    if (j.contains("font")) j.at("font").get_to(text.font);
    if (j.contains("color")) j.at("color").get_to(text.color);
    if (j.contains("fontSize")) j.at("fontSize").get_to(text.fontSize);
    if (j.contains("centered")) j.at("centered").get_to(text.centered);
    if (j.contains("font_id")) j.at("font_id").get_to(text.font_id);
}

void from_json(const nlohmann::json& j, Button& button)
{
    if (j.contains("text")) j.at("text").get_to(button.text);
    if (j.contains("size")) j.at("size").get_to(button.size);
    if (j.contains("font")) j.at("font").get_to(button.font);
    if (j.contains("color")) j.at("color").get_to(button.color);
    if (j.contains("fontSize")) j.at("fontSize").get_to(button.fontSize);
    if (j.contains("font_id")) j.at("font_id").get_to(button.font_id);

    if (j.contains("input")) j.at("input").get_to(button.input);
    if (j.contains("content")) j.at("content").get_to(button.content);

    if (j.contains("entity")) j.at("entity").get_to(button.entity);
    if (j.contains("action")) j.at("action").get_to(button.action);
}

}  // namespace RType

#endif  // FROMJSON_HPP