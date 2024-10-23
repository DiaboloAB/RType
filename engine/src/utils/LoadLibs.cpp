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

// int LoadLibs::Start(std::string displayLib)
// {
//     std::cout << "Starting core..." << std::endl;
//     std::cout << displayLib << std::endl;
//     displayLibraries();
//     if (_displays.find(displayLib) == _displays.end())
//     {
//         std::cerr << "Error: Display library not found" << std::endl;
//         return 84;
//     }
//     _currentLib = displayLib;
//     std::cout << "Current display library: " << displayLib << std::endl;
//     std::cout << "Current game library: " << _currentGame << std::endl;
//     Loop();
//     return 0;
// }

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

// void Core::Loop(void)
// {
//     bool running = true;

//     std::cout << "Starting game loop..." << std::endl;
//     _inGame = false;
//     _index = 0;
//     _module = 0;
//     _currentGame = "";

//     DISPLAY->init();
//     DISPLAY->setMapSize(DVEC(30, 20));
//     while (running)
//     {
//         checkSwitch();
//         DISPLAY->clear();
//         getInputs();
//         if (_inputs[Arcade::Games::KeyType::QUIT] == 1) {
//             running = false;
//             break;
//         }
//         _deltaT = DISPLAY->getDeltaT();
//         if (_inGame) {
//             GAME->update(_inputs, _deltaT);
//             if (_inputs[Arcade::Games::KeyType::ESC] == 1) {
//                 DISPLAY->setMapSize(DVEC(30, 20));
//                 _inGame = false;
//                 _score.addScore(_currentGame, _name, stoi(GAME->getScore()));
//             }
//             setTiles();
//             setTexts();
//             DISPLAY->displayGame();
//         } else {
//             if (_inputs[Arcade::Games::KeyType::ESC] == 1) {
//                 running = false;
//             }
//             displayMenu();
//         }
//     }
//     if (_currentGame != "")
//         GAME->close();
//     DISPLAY->close();
// }
