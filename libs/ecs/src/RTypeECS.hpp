/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANTIT_H
#define ANTIT_H

#include <iostream>

#include "entity/EntityManager.hpp"

// std

namespace RType::ECS
{

class Registry
{
   public:
    Registry();
    ~Registry();

    Entity create();
    void kill(Entity entity);

    // Getters

    // Setters

   private:
    EntityManager _entityManager;
    // Member variables
};

}  // namespace RType::ECS

#endif  // ANTIT_H