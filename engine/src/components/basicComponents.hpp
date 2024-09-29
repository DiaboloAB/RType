/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef BASICCOMPONENTS_H
#define BASICCOMPONENTS_H

// std

namespace RType {
    struct Position
    {
        float x;
        float y;

        Position(float x, float y) : x(x), y(y) {}
    };

    struct Velocity
    {
        float x;
        float y;

        Velocity(float x, float y) : x(x), y(y) {}
    };
}

#endif // BASICCOMPONENTS_H