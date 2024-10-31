/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include "common/components/components.hpp"
#include "common/components/uiComponents.hpp"
#include "common/network/components/networkComp.hpp"

#define COMPONENT_TYPES \
    Transform, Sprite, Animator, Sticky, Hitbox, EventManager, RigidBody, Collider, \
    NetworkRoom, NetworkClient, NetworkData, \
    Text, Button

#endif  // COMPONENTLIST_H