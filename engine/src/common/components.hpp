/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <mlg/mlg.hpp>
// std

namespace RType
{
struct Transform
{
    mlg::vec3 position;
    mlg::vec3 rotation;
    mlg::vec3 scale;

    Transform(mlg::vec3 position, mlg::vec3 rotation, mlg::vec3 scale)
        : position(position), rotation(rotation), scale(scale)
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
}  // namespace RType

#endif  // COMPONENTS_H