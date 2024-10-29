/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#include "common/network/cppScripts/ComServer.hpp"
#include "common/cppScripts/HelloWorld.hpp"
#include "common/cppScripts/AnimLaserCharge.hpp"
#include "common/cppScripts/MovePlayer.hpp"
#include "common/cppScripts/PlayerShoot.hpp"
#include "common/cppScripts/AnimPlayer.hpp"
#include "common/cppScripts/AnimThruster.hpp"
#include "common/cppScripts/MoveLaser.hpp"

#define SCRIPT_TYPES ComServer, HelloWorld, AnimLaserCharge, MovePlayer, PlayerShoot, AnimPlayer, AnimThruster, MoveLaser

#endif  // SCRIPTLIST_H