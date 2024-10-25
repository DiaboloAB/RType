/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "ArgParser.hpp"

namespace RType::Network
{

ArgParser::ArgParser(int nb_args, char **flags)
{
    try
    {
        if (nb_args % 2 != 1)
            throw ArgParserError("\x1B[31m[ArgParser Error]\x1B[0m: Invalid number of arguments.");
        this->parseFlags(&flags[1], nb_args - 1);
    }
    catch (ArgParserError &e)
    {
        throw;
    }
}

ArgParser::ArgParser(const ArgParser &obj) : _host(obj._host), _port(obj._port) {}

ArgParser::~ArgParser() {}

void ArgParser::setHost(std::string const host) { this->_host = host; }

std::string ArgParser::getHost() { return this->_host; }

unsigned int ArgParser::getPort() { return this->_port; }

void ArgParser::setPort(const unsigned int port)
{
    if (port < 1024 || port > 65535)
        throw ArgParserError("\x1B[31m[ArgParser Error]\x1B[0m: Chose a port between 1024 and 65535.");
    this->_port = port;
}

void ArgParser::parseFlags(char **flags, int nb_args)
{
    try
    {
        for (size_t i = 0; i < nb_args; i += 2)
        {
            std::string flag = flags[i];
            if (flag == "-p" || flag == "--port")
                this->setPort((unsigned int)std::stoi(flags[i + 1]));
            else if ((flag == "-H" || flag == "--host"))
                this->setHost(flags[i + 1]);
            else
                throw ArgParserError(std::string("\x1B[31m[ArgParser Error]\x1B[0m: Unknown flag ") + flag);
        }
    }
    catch (ArgParserError &e)
    {
        throw;
    }
    catch (std::exception &e)
    {
        throw ArgParserError(std::string("\x1B[31m[ArgParser Error]\x1B[0m: {") + e.what() + "}");
    }
    std::cerr << "\x1B[32m[ArgParser]\x1B[0m: Server flags set." << std::endl;
}

ArgParser &ArgParser::operator=(const ArgParser &obj)
{
    if (&obj == this) return *this;
    this->_host = obj._host;
    this->_port = obj._port;
    return *this;
}
}  // namespace RType::Network
