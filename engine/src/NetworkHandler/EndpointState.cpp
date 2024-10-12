/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <NetworkHandler/EndpointState.hpp>

namespace RType::Network
{

EndpointState::EndpointState(){};
EndpointState::~EndpointState(){};

bool EndpointState::getConnected() const { return this->_connected; }

std::chrono::time_point<std::chrono::steady_clock> EndpointState::getLastPing() const
{
    return this->_lastPing;
}

uint32_t EndpointState::getNetworkId() const { return this->_networkId; }

void EndpointState::setConnected(bool newConnected) { this->_connected = newConnected; }

void EndpointState::setLastPing(std::chrono::time_point<std::chrono::steady_clock> newLastPing)
{
    this->_lastPing = newLastPing;
}

void EndpointState::setNetworkId(uint32_t newNetworkId) { this->_networkId = newNetworkId; }

}  // namespace RType::Network