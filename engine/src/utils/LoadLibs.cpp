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
}

RType::LoadLibs::~LoadLibs()
{
}

void RType::LoadLibs::addLibraries(const std::string &fileName)
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
    std::cout << "----- Dynamic libraries -----" << std::endl;

    std::string fullPath = path + fileName;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type != DT_DIR && entry->d_name == fileName) {
            std::cout << "Adding libraries from path: " << fullPath << std::endl;
            try {
                _displays = _displayLoader.getInstance(fullPath, "displayEntryPoint");
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
    closedir(dir);
}
