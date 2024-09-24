/*
** EPITECH PROJECT, 2024
** RType
** File description:
** main.cpp
*/

#include "RTypeEngine.hpp"
#include "Server.hpp"
#include <string>
#include <iostream>

int main(int ac, char **av)
{
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) {
        std::cout << "Usage : ./r-type_server" << std::endl;
        return 0;
    }
    return 0;
}
