/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef FROMJSONNETWORK_HPP
#define FROMJSONNETWORK_HPP

#include <nlohmann/json.hpp>

#include "networkComp.hpp"

namespace RType
{
void from_json(const nlohmann::json& j, NetworkClient& networkClient) {}

void from_json(const nlohmann::json& j, NetworkData& networkData)
{
    if (j.contains("id")) j.at("id").get_to(networkData._id);
    if (j.contains("authority")) j.at("authority").get_to(networkData._authority);
}
}  // namespace RType

#endif  // FROMJSONNETWORK_HPP