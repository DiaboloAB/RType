/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "mobs.hpp"

using namespace mobs;

Registry::Registry() { std::cout << "----- Registry -----" << std::endl; }

Registry::~Registry() {}

Entity Registry::create() { return _entityManager.create(); }

void Registry::kill(Entity entity) { _entityManager.kill(entity); }

void Registry::clear()
{
    for (Entity entity : _entityManager)
    {
        kill(entity);
    }
}