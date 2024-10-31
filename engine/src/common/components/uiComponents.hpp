/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef UICOMPONENTS_H
#define UICOMPONENTS_H

#include <mlg/mlg.hpp>

#include "../../utils/Event.hpp"
#include "Client.hpp"
#include "animations/AnimationList.hpp"
#include "mobs/mobs.hpp"

// std
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#ifdef _WIN32
#include <sstream>
#endif

namespace RType
{

struct Text
{
    std::string text = "";
    std::string font = "";
    mlg::vec3 color = mlg::vec3(1.0f);
    int fontSize = 12;
    bool centered = false;
    int font_id = -1;

    Text() {}
    static constexpr const char* name = "Text";
};

struct Button
{
    std::string text = "";
    mlg::vec3 size = mlg::vec3(1.0f);
    std::string font = "";
    mlg::vec3 color = mlg::vec3(1.0f);
    int fontSize = 12;
    int font_id = -1;
    bool selected = false;

    bool input = false;
    std::string content = "";
    bool virtualKeyboard = false;

    // std::string target = "";
    // std::string action = "";

    Button() {}
    static constexpr const char* name = "Button";
};

}  // namespace RType

#endif  // COMPONENTS_H