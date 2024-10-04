/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef VEC4_H
#define VEC4_H

// std

namespace mlg
{

class vec4 {
public:
    float x, y, z, w;

    vec4() {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    explicit vec4(float value) : x(value), y(value), z(value), w(value) {}
    ~vec4() {}

    // Getters

    // Setters

private:
    // Member variables
};

} // namespace mlg

#endif // VEC4_H