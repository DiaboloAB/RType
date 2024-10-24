/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef GETBINARYPATH_H
#define GETBINARYPATH_H

#include <string>

#ifdef WIN32
#include <windows.h>

std::string getBinaryPath()
{
    char result[MAX_PATH];
    GetModuleFileNameA(NULL, result, MAX_PATH);
    return std::string(result);
}

#else
#include <linux/limits.h>
#include <unistd.h>

std::string getBinaryPath()
{
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? count : 0);
}

#endif

std::string getAssetsPath()
{
    std::string binaryPath = getBinaryPath();
    std::filesystem::path binaryDir = std::filesystem::path(binaryPath).parent_path();
    std::filesystem::path assetsDir = binaryDir / "assets/";
    return assetsDir.string();
}

#endif  // GETBINARYPATH_H