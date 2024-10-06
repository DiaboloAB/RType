/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <cstring>
#include <iostream>
#include <string>

#include "PacketManager/CreateEntityPacket.hpp"
#include "RTypeEngine.hpp"

static void displayUsage(void)
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\n  ./r-client [[OPTION] [PARAM1] [PARAM2]]" << std::endl;
    std::cout << "\nOPTION:" << std::endl;
    std::cout
        << "  -d  --debug : Creation of client with server host/port without using graphic part."
        << std::endl;
    std::cout << "\nPARAM:" << std::endl;
    std::cout << "\n  host : Server ip address." << std::endl;
    std::cout << "  port : Server port between 1024 and 65535." << std::endl;
}

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
    {
        displayUsage();
        return 0;
    }
    try
    {
        if (ac == 1)
        {
            RType::Engine engine;
            engine.run();
        }
        else if (ac != 1 && (std::string(av[1]) == "--debug" || std::string(av[1]) == "-d"))
        {
            std::string host = av[2];
            RType::Engine engine(host, (unsigned int)std::stoi(av[3]), false);
            engine.run();
        }
        else
        {
            displayUsage();
        }
        return 0;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        displayUsage();
    }
}
