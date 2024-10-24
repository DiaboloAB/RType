/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <cstring>
#include <iostream>
#include <string>

#include "RTypeEngine.hpp"

int main(int ac, char **av)
{
    std::map<std::string, std::string> args;

    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        size_t pos = arg.find('=');
        if (pos != std::string::npos)
        {
            std::string key = arg.substr(0, pos);
            std::string value = arg.substr(pos + 1);
            args[key] = value;
        }
    }

    try
    {
        RType::Engine engine;
        engine.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
