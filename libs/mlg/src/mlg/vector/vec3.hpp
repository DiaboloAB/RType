/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef MLGVECTOR_H
#define MLGVECTOR_H

// std
#include <cmath>

namespace mlg
{

class vec3
{
   public:
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}

    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    explicit vec3(float value) : x(value), y(value), z(value) {}

    vec3 cross(const vec3& other) const
    {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }

    float dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z; }

    float length() const { return sqrt(x * x + y * y + z * z); }

    vec3 normalize() const
    {
        float len = length();
        return {x / len, y / len, z / len};
    }

    vec3 operator+(const vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }

    vec3 operator-(const vec3& other) const { return {x - other.x, y - other.y, z - other.z}; }

    vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
};

}  // namespace mlg

#endif  // MLGVECTOR_H