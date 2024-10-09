/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "hexaColorToVec3.hpp"

mlg::vec3 hexaColorToVec3(const std::string& hexa)
{
    mlg::vec3 color;

    try
    {
        if (hexa.size() != 7)
        {
            throw std::invalid_argument("Invalid hex format, should be #RRGGBB");
        }

        color.x = std::stoul(hexa.substr(1, 2), nullptr, 16) / 255.0f;  // Red
        color.y = std::stoul(hexa.substr(3, 2), nullptr, 16) / 255.0f;  // Green
        color.z = std::stoul(hexa.substr(5, 2), nullptr, 16) / 255.0f;  // Blue

        return color;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << std::endl;
        return mlg::vec3(0.0f, 0.0f, 0.0f);
    }
}
