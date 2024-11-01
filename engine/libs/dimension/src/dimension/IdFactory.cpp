/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-11-01
 *   Location: Rennes
 **********************************************************************************/

#include "IdFactory.hpp"

namespace dimension
{

IdFactory::IdFactory(){};

IdFactory::~IdFactory(){};

uint32_t IdFactory::generateNetworkId()
{
    uint32_t givenId = 0;

    if (this->_reusable.size() == 0 && this->_networkId == MAX_NID)
        throw new IdFactoryError("All ids are in use. Try later.");
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

void IdFactory::becomeReusable(NetworkId reusable)
{
    if (reusable >= this->_networkId)
        throw new IdFactoryError("ID given can't be reusable if he wasn't assign.");
    this->_reusable.push(reusable);
}
}  // namespace dimension