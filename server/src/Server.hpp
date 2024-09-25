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
    class Server {

        public:
            Server(int nb_args, char **flags);
            Server(const Server &obj);
            ~Server();

        public:
            void setHost(std::string const host);
            std::string getHost();
            void setPort(const unsigned int port);
            unsigned int getPort();

        public:
            void parseFlags(char **flags, int nb_args);

        public:
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
