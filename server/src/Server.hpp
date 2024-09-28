/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <exception>
    #include <string>

namespace RType::Server
{
    /**
     * @class Server
     * @brief Class used to parse argc argv arguments given by server binary to get server host and port.
     */
    class Server {
        public:
            /**
             * @brief Construct Server object used to parse flags. If no args default values are
             * 0.0.0.0 for the host and 8581 for the port
             * 
             * @param nb_args: equivalent of argc.
             * @param flags: equivalent of argv.
             * @return Server object or throw in case of invalid argc, argv.
             */
            Server(int nb_args, char **flags);

            /**
             * @brief Construct Server object and copy obj content in it.
             * 
             * @param nb_args: Server to be copied.
             * @return Server object.
             */
            Server(const Server &obj);

            /**
             * @brief Destruct server object.
             */
            ~Server();

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
             * @brief Copy the values of Server object passed as parameter.
             * 
             * @param obj: Server to be copied.
             * @return Reference to server with new values.
             */
            Server &operator=(const Server &obj);
        
        public:
            class ServerError : public std::exception {
                public:
                    ServerError(std::string msg) : _msg(msg) {};
                    ~ServerError() {};
                private:
                    const char *what() const noexcept override {return _msg.c_str();};
                private:
                    std::string _msg;
            };

        private:
            std::string _host = "0.0.0.0";
            unsigned int _port = 8581;
    };
}
