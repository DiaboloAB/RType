/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "ISystem.hpp"

// std
#include <vector>
#include <memory>

namespace RType {

class SystemManager {
public:
    SystemManager();
    ~SystemManager();

    template <typename T, typename... Args>
    T &addSystem(Args &&...args) {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T& ref = *system;
        _systems.push_back(std::move(system));
        return ref;
    }

    void start(ECS::Registry &registry, GameContext &gameContext) {
        for (auto &system : _systems) {
            system->start(registry, gameContext);
        }
    }

    void update(ECS::Registry &registry, GameContext &gameContext) {
        for (auto &system : _systems) {
            system->update(registry, gameContext);
        }
    }

    void draw(ECS::Registry &registry, GameContext &gameContext) {
        for (auto &system : _systems) {
            system->draw(registry, gameContext);
        }
    }

    // Getters

    // Setters

private:
    // Member variables
    std::vector<std::unique_ptr<ISystem>> _systems;
};

} // namespace RType

#endif // SYSTEMMANAGER_H
