/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <mlg/mlg.hpp>

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
struct Basics
{
    std::string tag;
    std::string layer;
    bool staticObject = false;

    Basics() {}
    Basics(std::string tag, std::string layer, bool staticObject)
        : tag(tag), layer(layer), staticObject(staticObject)
    {
    }
};

struct Transform
{
    mlg::vec3 position;
    mlg::vec3 rotation;
    mlg::vec3 scale;

    Transform(mlg::vec3 position, mlg::vec3 rotation, mlg::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform(mlg::vec3 position)
        : position(position), rotation(mlg::vec3(0.0f)), scale(mlg::vec3(1.0f))
    {
    }

    Transform() : position(mlg::vec3(0.0f)), rotation(mlg::vec3(0.0f)), scale(mlg::vec3(1.0f)) {}
};

struct RigidBody
{
    RigidBody() {}
};

struct Sprite
{
    std::string filePath;
    int id = -1;

    Sprite() {}
    Sprite(std::string filePath) : filePath(filePath) {}
};

struct Animator
{
    AnimationList animations = AnimationList();

    Animator() {}
};

struct Sticky
{
    std::string target;
    mlg::vec3 offset = mlg::vec3();

    Sticky(){};
};

struct Button
{
    std::string text;
    mlg::vec3 size;
    std::string font;
    mlg::vec3 color;

    std::string target = "";
    std::string action = "";

    Button(std::string text, mlg::vec3 size, std::string font, mlg::vec3 color)
        : text(text), size(size), font(font), color(color)
    {
    }
    Button(std::string text, mlg::vec3 size, std::string font, mlg::vec3 color, std::string target,
           std::string action)
        : text(text), size(size), font(font), color(color), target(target), action(action)
    {
    }
};
struct Text
{
    std::string text;
    mlg::vec3 color;
    std::string font;
    std::string id_font;
    int fontSize;

    Text(std::string text, mlg::vec3 color, std::string font, int fontSize)
        : text(text), color(color), font(font), fontSize(fontSize)
    {
    }
};

struct Dialog
{
    std::vector<std::string> lines;
    mlg::vec3 color;
    std::string font;
    int fontSize;

    Dialog(std::string text, mlg::vec3 color, std::string font, int fontSize)
        : color(color), font(font), fontSize(fontSize)
    {
        std::istringstream stream(text);
        std::string line;
        while (std::getline(stream, line))
        {
            lines.push_back(line);
        }
    }
};

struct Audio
{
    std::vector<std::string> sounds;
    std::vector<std::string> musics;
    int musicVolume = 50;
    int soundVolume = 50;
    int soundID;

    std::queue<std::string> audioQueue;

    Audio() {}
    Audio(std::vector<std::string> sounds, std::vector<std::string> musics)
        : sounds(sounds), musics(musics)
    {
    }
};
}  // namespace RType

#endif  // COMPONENTS_H