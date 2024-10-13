/*
** EPITECH PROJECT, 2024
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include <string>

#include "RTypeEngine.hpp"
#include "Server.hpp"

static void displayUsage()
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\n  ./r-type_server [-p port] [-H host]" << std::endl;
    std::cout << "\nPARAM:" << std::endl;
    std::cout << "  -p  --port : Server port between 1024 and 65535." << std::endl;
    std::cout << "  -H  --host : Server ip address." << std::endl;
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
        RType::Server::Server server(ac, av);
        RType::Engine engine(server.getHost(), server.getPort(), true, false);
        engine.run();
        return 0;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        displayUsage();
    }
}
