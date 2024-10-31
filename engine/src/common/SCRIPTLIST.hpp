/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#include "common/cppScripts/AnimLaserCharge.hpp"
#include "common/cppScripts/AnimPlayer.hpp"
#include "common/cppScripts/AnimThruster.hpp"
#include "common/cppScripts/Bullet.hpp"
#include "common/cppScripts/GameManager.hpp"
#include "common/cppScripts/HelloWorld.hpp"
#include "common/cppScripts/Menu.hpp"
#include "common/cppScripts/MoveLaser.hpp"
#include "common/cppScripts/MovePlayer.hpp"
#include "common/cppScripts/PlayerShoot.hpp"
#include "common/cppScripts/RedShip.hpp"
#include "common/cppScripts/Terrain.hpp"
#include "common/network/cppScripts/ClientRedirect.hpp"
#include "common/network/cppScripts/ComServer.hpp"
#include "common/network/cppScripts/RoomRedirect.hpp"

#define SCRIPT_TYPES                                                                           \
    HelloWorld, AnimLaserCharge, MovePlayer, PlayerShoot, AnimPlayer, AnimThruster, MoveLaser, \
        Bullet, RedShip, GameManager, Terrain, Menu, ClientRedirect, RoomRedirect, ComServer

#endif  // SCRIPTLIST_H