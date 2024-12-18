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
#include "common/components/adminComponents.hpp"

#define COMPONENT_TYPES                                                                       \
    Transform, Sprite, Animator, Sticky, NetworkClient, NetworkData, EventManager, RigidBody, \
        Collider, Text, Button, NetworkRoom, Audio, \
        Console, Metrics

#endif  // COMPONENTLIST_H