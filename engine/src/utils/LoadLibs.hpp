/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef LoadLibs_H
#define LoadLibs_H

#include "../IRuntime/IRuntime.hpp"
#include "DLLoader.hpp"

// std
#include <iostream>
#include <stdexcept>
#include <string>

namespace RType
{

class LoadLibs
{
   private:
   private:
    void addLibraries(const std::string &path);

    DLLoader<IRuntime> _displayLoader;
    std::string _currentLib;

   public:
    LoadLibs();
    ~LoadLibs();

    void displayLibraries(void);

    std::map<std::string, std::shared_ptr<IRuntime>> _displays;
};

}  // namespace RType

#endif  // LoadLibs_H
