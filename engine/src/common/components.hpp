/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <mlg/mlg.hpp>

#include "animations/AnimationList.hpp"
#include "mobs/mobs.hpp"
#include "timer/Timer.hpp"

// std
#include <iostream>
#include <string>
#include <vector>
#include <queue>

namespace RType
{
struct NetworkComp
{
    uint32_t id;
    std::string authority;

    NetworkComp(uint32_t id, std::string authority) : id(id), authority(authority){};
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

struct Velocity
{
    mlg::vec3 velocity;

    Velocity(mlg::vec3 velocity) : velocity(velocity) {}
};

struct Sprite
{
    std::string filePath;

    Sprite(std::string filePath) : filePath(filePath) {}
};

struct Animator
{
    AnimationList animations = AnimationList();

    Animator() {}
};

struct CoolDown
{
    Timer timer;

    CoolDown(bool active)
    {
        if (active) timer.start();
    }
};

struct Hitbox
{
    mlg::vec3 size;
    mlg::vec3 offset;
    bool isEnemy;

    Hitbox(mlg::vec3 size, mlg::vec3 offset, bool isEnemy)
        : size(size), isEnemy(isEnemy), offset(offset)
    {
    }
};

struct Health
{
    int health;

    Health(int health) : health(health) {}
};

struct Basics
{
    std::string tag;
    bool staticObject;

    Basics(std::string tag, bool staticObject) : tag(tag), staticObject(staticObject) {}
};

struct Button
{
    std::string text;
    mlg::vec3 size;
    std::string font;
    bool clicked;

    Button(std::string text, mlg::vec3 size, std::string font)
        : text(text), size(size), font(font), clicked(false)
    {
    }
};

struct Input
{
    std::string input = "";
    bool selected = false;
};

struct Ally
{
    mlg::vec3 moveDirection;

    Ally(mlg::vec3 moveDirection) : moveDirection(moveDirection) {}
    Ally() : moveDirection(mlg::vec3(0.0f)) {}
};

struct Text
{
    std::string text;
    mlg::vec3 color;
    std::string font;
    int fontSize;

    Text(std::string text, mlg::vec3 color, std::string font, int fontSize)
        : text(text), color(color), font(font), fontSize(fontSize)
    {
    }
};

struct Paragraph
{
    std::vector<std::string> lines;
    mlg::vec3 color;
    std::string font;
    int fontSize;

    Paragraph(std::string text, mlg::vec3 color, std::string font, int fontSize)
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

    std::queue<std::string> audioQueue;

    Audio(std::vector<std::string> sounds, std::vector<std::string> musics)
        : sounds(sounds), musics(musics)
    {
    }
};

}  // namespace RType

#endif  // COMPONENTS_H