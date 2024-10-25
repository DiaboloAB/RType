/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef FROMJSONNETWORK_HPP
#define FROMJSONNETWORK_HPP

#include <nlohmann/json.hpp>

#include "components.hpp"

namespace RType
{
void from_json(const nlohmann::json& j, NetworkClient& networkClient) {}
}  // namespace RType

#endif  // FROMJSONNETWORK_HPP