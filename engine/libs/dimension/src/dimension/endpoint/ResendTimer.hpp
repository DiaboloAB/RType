/**********************************************************************************
 *   Project: Dimension Network
 *   Description: Networking Game Library
 *   Author: Morgan LARGEOT, Maxence LARGEOT
 *   Create Time: 2024-10-26
 *   Location: Rennes
 **********************************************************************************/
#pragma once

#include <asio.hpp>
#include <chrono>

namespace dimension
{
struct ResendTimer
{
    asio::ip::udp::endpoint _sender;
    std::chrono::steady_clock::time_point _timer;

    ResendTimer(asio::ip::udp::endpoint sender) : _sender(sender)
    {
        _timer = std::chrono::steady_clock::now();
    }
    ~ResendTimer() {}
};
}  // namespace dimension