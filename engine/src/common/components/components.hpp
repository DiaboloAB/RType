/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

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
struct Basics
{
    std::string tag = "Entity";
    std::string layer = "Default";
    bool staticObject = false;

    Basics() {}
    Basics(std::string tag, std::string layer, bool staticObject)
        : tag(tag), layer(layer), staticObject(staticObject)
    {
    }
    static constexpr const char* name = "Basics";
};

struct Transform
{
    mlg::vec3 position = mlg::vec3(0.0f);
    mlg::vec3 rotation = mlg::vec3(0.0f);
    mlg::vec3 scale = mlg::vec3(1.0f);

    Transform() {}
    static constexpr const char* name = "Transform";
};

struct RigidBody
{
    mlg::vec3 velocity;
    mlg::vec3 acceleration;
    float mass = 1.0f;
    float drag = 0.0f;

    RigidBody() {}
    static constexpr const char* name = "RigidBody";
};

struct Sprite
{
    std::string filePath;
    int id = -1;

    Sprite() {}
    static constexpr const char* name = "Sprite";
};

struct Animator
{
    AnimationList animations = AnimationList();

    Animator() {}
    static constexpr const char* name = "Animator";
};

struct Sticky
{
    std::string target;
    mlg::vec3 offset = mlg::vec3();

    Sticky() {};
    static constexpr const char* name = "Sticky";
};

struct Hitbox
{
    mlg::vec3 size = mlg::vec3(1.0f);
    mlg::vec3 offset = mlg::vec3(0.0f);

    Hitbox() {};
    static constexpr const char* name = "Hitbox";
};

struct Button
{
    std::string text;
    mlg::vec3 size;
    std::string font;
    mlg::vec3 color;

    std::string target = "";
    std::string action = "";

    Button() {}
    static constexpr const char* name = "Button";
};
struct Text
{
    std::string text = "";
    mlg::vec3 color = mlg::vec3(1.0f);
    std::string font = "";
    int id_font = -1;
    int fontSize = 12;

    Text() {}
    static constexpr const char* name = "Text";
};

struct Audio
{
    std::vector<std::string> sounds;
    std::vector<std::string> musics;
    int musicVolume = 50;
    int soundVolume = 50;
    int soundID = 0;

    std::queue<std::string> audioQueue;

    Audio() {}
    static constexpr const char* name = "Audio";
};

struct Collider
{
    mlg::vec3 size;
    bool isTrigger = false;
    std::vector<std::tuple<mobs::Entity, mlg::vec3>> collisions;

    Collider() {}
    static constexpr const char* name = "Collider";
};

struct EventManager
{
    std::vector<Event> eventList;

    EventManager() {}
    static constexpr const char* name = "EventManager";
};

}  // namespace RType

#endif  // COMPONENTS_H