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

struct RigidBody {
    mlg::vec3 velocity;
    mlg::vec3 acceleration;
    float mass = 1.0f;
    float restitution = 0.5f;
    bool Physic = false;

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


#define ENTER 1
#define EXIT 2
#define STAY 3
struct Collider
{
    mlg::vec3 size;
    bool isTrigger = false;
    std::vector<mobs::Entity> collisions;
    std::vector<std::string> layerMask;

    int isColliding(mlg::vec3 position,
        mobs::Entity entity, mlg::vec3 otherPosition, mlg::vec3 otherSize)
    {

        if (position.x < otherPosition.x + otherSize.x &&
            position.x + size.x > otherPosition.x &&
            position.y < otherPosition.y + otherSize.y &&
            position.y + size.y > otherPosition.y) {
            if (std::find(collisions.begin(), collisions.end(), entity) != collisions.end()) {
                return STAY;
            }
            collisions.push_back(entity);
            return ENTER;
        }
        if (std::find(collisions.begin(), collisions.end(), entity) != collisions.end()) {
            collisions.erase(std::remove(collisions.begin(), collisions.end(), entity), collisions.end());
            return EXIT;
        }

        return 0;
    }

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