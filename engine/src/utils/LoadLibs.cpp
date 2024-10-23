/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** Core
*/

#include "DLLoader.hpp"
#include "LoadLibs.hpp"

#include <dirent.h>
#include <list>
#include <map>
#include <memory>
#include <string>

static std::string nameList = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";

#define DISPLAY _displays[_currentLib]

RType::LoadLibs::LoadLibs()
{
    const size_t path_max = 256;
    char path[path_max] = "./lib/";
    DIR *dir;

    dir = opendir(path);
    if (dir == NULL)
    {
        std::cerr << "Error: cannot open directory" << std::endl;
        exit(84);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type != DT_DIR)
            addLibraries(path + std::string(entry->d_name));
    }
    closedir(dir);
}

RType::LoadLibs::~LoadLibs()
{
}

void RType::LoadLibs::addLibraries(const std::string &path)
{
    std::cout << "Adding libraries from path: " << path << std::endl;
    try {
        _displays[path] = _displayLoader.getInstance(path, "displayEntryPoint");
        std::cout << "Display library loaded: " << path << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RType::LoadLibs::displayLibraries(void)
{
    std::cout << "Displays:" << std::endl;
    for (auto &display : _displays)
    {
        std::cout << display.first << std::endl;
    }
    std::cout << std::endl;
}
