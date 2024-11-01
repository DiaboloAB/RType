/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <mlg/mlg.hpp>
#include <string>
#include <vector>

class Event
{
   private:
   public:
    Event() {}
    ~Event() {}

    std::string prefab = "";
    mlg::vec3 position = mlg::vec3(0.0f);
    mlg::vec3 scale = mlg::vec3(1.0f);
    std::string type = "";

    float delay = 0.0f;
};

#endif  // EVENT_HPP
