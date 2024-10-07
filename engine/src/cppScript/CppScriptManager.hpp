/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef CPPSCRIPTMANAGER_H
#define CPPSCRIPTMANAGER_H

#include "ICppScript.hpp"
#include "common/cppScripts/helloworld.hpp"
// std
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace RType
{

class CppScriptManager {
public:
    CppScriptManager();
    ~CppScriptManager();

    using ScriptCreateFn = std::function<std::unique_ptr<ICppScript>()>;

    static void registerScript(const std::string &name, ScriptCreateFn createFn)
    {
        std::cout << "Registering script " << name << std::endl;
        try {
            getScriptRegistry()[name] = std::move(createFn);
            std::cout << "Script " << name << " registered" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Failed to register script: " << e.what() << std::endl;
        }
    }

    static std::unique_ptr<ICppScript> createScript(const std::string &name)
    {
        auto &registry = getScriptRegistry();
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr;
    }

private:
    void initScripts()
    {
        registerScript("HelloWorld", []() {
            return std::make_unique<HelloWorldScript>();
        });

        std::cout << "All scripts have been initialized." << std::endl;
    }

    static std::unordered_map<std::string, ScriptCreateFn> &getScriptRegistry()
    {
        static std::unordered_map<std::string, ScriptCreateFn> registry;
        return registry;
    }
};

} // namespace RType

#endif // CPPSCRIPTMANAGER_H