/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <NetworkHandler/NetworkIdHandler.hpp>

namespace RType::Network
{

NetworkIdHandler::NetworkIdHandler(){};

NetworkIdHandler::~NetworkIdHandler(){};

uint32_t NetworkIdHandler::generateNetworkId()
{
    uint32_t givenId = 0;

    if (this->_reusable.size() == 0 && this->_networkId == MAX_NID)
        throw new NetworkIdHandlerError("All ids are in use. Try later.");
    if (this->_reusable.size() != 0)
    {
        givenId = this->_reusable.front();
        this->_reusable.pop();
    }
    else
    {
        givenId = this->_networkId;
        this->_networkId++;
    }
    return givenId;
}

void NetworkIdHandler::becomeReusable(NetworkId reusable)
{
    if (reusable >= this->_networkId)
        throw new NetworkIdHandlerError("ID given can't be reusable if he wasn't assign.");
    this->_reusable.push(reusable);
}
}  // namespace RType::Network
