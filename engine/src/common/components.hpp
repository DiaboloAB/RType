/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <glm/glm.hpp>
// std

namespace RType
{
struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
    {
    }
    Transform() : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)) {}
};

struct Velocity
{
    glm::vec3 velocity;

    Velocity(glm::vec3 velocity) : velocity(velocity) {}
};

struct Sprite
{
    std::string filePath;

    Sprite(std::string filePath) : filePath(filePath) {}
};
}  // namespace RType

#endif  // COMPONENTS_H