/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <exception>
#include "APacket.hpp"
#include "HiServerPacket.hpp"
#include "HiClientPacket.hpp"
#include "AdiosServerPacket.hpp"
#include "HealthcheckPacket.hpp"
#include "CreateEntityPacket.hpp"
#include "DestroyEntityPacket.hpp"
#include "MoveEntityPacket.hpp"
#include "UpdateEntityPacket.hpp"
#include "KickClientPacket.hpp"
#include "PacketValidationPacket.hpp"
#include "ClientEventPacket.hpp"

namespace RType::Network {
    class PacketFactory {
        public:
            PacketFactory();
            PacketFactory(const PacketFactory &obj);
            ~PacketFactory();
        public:
            std::unordered_map<PacketType, std::function<std::shared_ptr<APacket>(std::vector<char> &)>> getCreationMap() const;
            std::shared_ptr<APacket> createPacketFromBuffer(std::vector<char> &buffer);
        public:
            class PacketFactoryError : public std::exception {
                public:
                    PacketFactoryError(std::string msg) : _msg(msg){};
                    ~PacketFactoryError(){};
                private:
                    const char *what() const noexcept override { return _msg.c_str(); };
                private:
                    std::string _msg;
            };
        private:
            std::unordered_map<PacketType, std::function<std::shared_ptr<APacket>(std::vector<char> &)>> _creationMap;
    };
}