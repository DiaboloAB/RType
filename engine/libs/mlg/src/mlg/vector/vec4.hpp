/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef VEC4_H
#define VEC4_H

// std
#include <algorithm>

namespace mlg
{

/**
 * @class vec4
 * @brief A 4-dimensional vector class.
 */
class vec4
{
   public:
    float x;  ///< The x component of the vector.
    float y;  ///< The y component of the vector.
    float z;  ///< The z component of the vector.
    float w;  ///< The w component of the vector.

    /**
     * @brief Default constructor for vec4.
     */
    vec4() {}

    /**
     * @brief Constructs a vec4 with specified x, y, z, and w components.
     *
     * @param x The x component.
     * @param y The y component.
     * @param z The z component.
     * @param w The w component.
     */
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    /**
     * @brief Constructs a vec4 with all components set to the same value.
     *
     * @param value The value to set all components to.
     */
    explicit vec4(float value) : x(value), y(value), z(value), w(value) {}

    static vec4 getIntersection(vec4 a, vec4 b) {
        float x = std::max(a.x, b.x);
        float y = std::max(a.y, b.y);
        float x2 = std::min(a.x + a.z, b.x + b.z);
        float y2 = std::min(a.y + a.w, b.y + b.w);

        if (x < x2 && y < y2) {
            return vec4(x, y, x2 - x, y2 - y);
        }
        return vec4(0, 0, 0, 0);
    }

    /**
     * @brief Destructor for vec4.
     */
    ~vec4() {}

   private:
    // Member variables
};

}  // namespace mlg

#endif  // VEC4_H