/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <iostream>
#include <string>

#include "ArgParser.hpp"
#include "MainServer.hpp"

static int displayUsage(int returnValue)
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\n  ./r-type_server [-p port] [-H host]" << std::endl;
    std::cout << "\nPARAM:" << std::endl;
    std::cout << "  -p  --port : Server port between 1024 and 65535." << std::endl;
    std::cout << "  -H  --host : Server ip address." << std::endl;
    return returnValue;
}

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h"))
        return displayUsage(0);
    try
    {
        RType::Network::ArgParser serverArgs(ac, av);
        RType::Network::MainServer server(serverArgs.getHost(), serverArgs.getPort());
        server.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return displayUsage(84);
    }
    return 0;
}
