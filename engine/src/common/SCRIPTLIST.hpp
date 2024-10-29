/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#include "common/cppScripts/HelloWorld.hpp"
#include "common/network/cppScripts/ComServer.hpp"
#include "common/network/cppScripts/ClientRedirect.hpp"
#include "common/network/cppScripts/RoomRedirect.hpp"

#define SCRIPT_TYPES ComServer, HelloWorld, ClientRedirect, RoomRedirect

#endif  // SCRIPTLIST_H