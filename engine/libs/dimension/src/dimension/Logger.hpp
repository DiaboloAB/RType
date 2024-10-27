/**********************************************************************************
 *  Project: Dimension Network
 *  Description: Networking Game Library
 *  Author: Morgan LARGEOT, Maxence LARGEOT
 *  Create Time: 2024-10-27
 *  Location: Rennes
  **********************************************************************************/

#pragma once

namespace dimension {
    #define LOG(file, msg) std::cerr << "\x1B[32m[" << file << "]\x1B[0m: " << msg << std::endl
    #define ERR_LOG(file, msg) std::cerr << "\x1B[31m[" << file << " Error]\x1B[0m: " << msg << std::endl
}