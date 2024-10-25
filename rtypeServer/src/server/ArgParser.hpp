/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <exception>
#include <string>
#include <iostream>

namespace RType::Network
{
/**
 * @class Server
 * @brief Class used to parse argc argv arguments given by server binary to get server host and
 * port.
 */
class ArgParser
{
   public:
    /**
     * @brief Construct ArgParser object used to parse flags. If no args default values are
     * 0.0.0.0 for the host and 8581 for the port
     *
     * @param nb_args: equivalent of argc.
     * @param flags: equivalent of argv.
     * @return ArgParser object or throw in case of invalid argc, argv.
     */
    ArgParser(int nb_args, char **flags);

    /**
     * @brief Construct ArgParser object and copy obj content in it.
     *
     * @param nb_args: ArgParser to be copied.
     * @return ArgParser object.
     */
    ArgParser(const ArgParser &obj);

    /**
     * @brief Destruct ArgParser object.
     */
    ~ArgParser();

   public:
    void setHost(std::string const host);
    std::string getHost();
    void setPort(const unsigned int port);
    unsigned int getPort();

   public:
    /**
     * @brief Parse flags to get host and port. Throws an error if flags are invalid.
     *
     * @param flags: equivalent of argv.
     * @param nb_args: equivalent of argc.
     */
    void parseFlags(char **flags, int nb_args);

   public:
    /**
     * @brief Copy the values of ArgParser object passed as parameter.
     *
     * @param obj: ArgParser to be copied.
     * @return Reference to ArgParser with new values.
     */
    ArgParser &operator=(const ArgParser &obj);

   public:
    class ArgParserError : public std::exception
    {
       public:
        ArgParserError(std::string msg) : _msg(msg){};
        ~ArgParserError(){};

       private:
        const char *what() const noexcept override { return _msg.c_str(); };

       private:
        std::string _msg;
    };

   private:
    std::string _host = "127.0.0.1";
    unsigned int _port = 8581;
};
}  // namespace RType::Network
