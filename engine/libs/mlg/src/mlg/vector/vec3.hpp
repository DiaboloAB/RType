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

/**
 * @class vec3
 * @brief A 3-dimensional vector class.
 */
class vec3
{
   public:
    float x;  ///< The x component of the vector.
    float y;  ///< The y component of the vector.
    float z;  ///< The z component of the vector.

    /**
     * @brief Default constructor for vec3.
     */
    vec3() : x(0), y(0), z(0) {}

    /**
     * @brief Constructs a vec3 with specified x, y, and z components.
     *
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     */
    vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * @brief Constructs a vec3 with all components set to the same value.
     *
     * @param value The value to set all components to.
     */
    explicit vec3(float value) : x(value), y(value), z(value) {}

    /**
     * @brief Destructor for vec3.
     */
    ~vec3() {}

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

    vec3 operator*(const vec3& other) const { return {x * other.x, y * other.y, z * other.z}; }

    vec3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }

    vec3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

    vec3& operator+=(const vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec3& operator-=(const vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec3& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
};

}  // namespace mlg

#endif  // MLGVECTOR_H