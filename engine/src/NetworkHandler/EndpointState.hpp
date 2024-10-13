/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <chrono>

namespace RType::Network
{
/**
 * @class EndpointState
 * @brief Represents the state of a network endpoint, tracking its connection status, last ping
 * time, and network ID.
 *
 * This class includes both getter and setter methods for its internal state, allowing for
 * the state of an endpoint to be easily modified and accessed.
 *
 * @note This class is thread-unsafe and should be managed carefully in multi-threaded environments.
 */
class EndpointState
{
   public:
    EndpointState();
    ~EndpointState();

   public:
    bool getConnected() const;
    std::chrono::time_point<std::chrono::steady_clock> getLastPing() const;
    uint32_t getNetworkId() const;

   public:
    void setConnected(bool newConnected);
    void setLastPing(std::chrono::time_point<std::chrono::steady_clock> newLastPing);
    void setNetworkId(uint32_t newNetworkId);

   private:
    bool _connected = false;
    std::chrono::time_point<std::chrono::steady_clock> _lastPing = std::chrono::steady_clock::now();
    uint32_t _networkId = 0;
};
}  // namespace RType::Network
