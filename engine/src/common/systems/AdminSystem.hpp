/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ADMINSYSTEM_H
#define ADMINSYSTEM_H

#include <system/ISystem.hpp>
// std
#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#endif



namespace RType
{

class AdminSystem : public ISystem
{
   public:
    AdminSystem() {}
    ~AdminSystem() {}


    void load(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Metrics>();
        for (auto entity : view)
        {
            auto &metrics = view.get<Metrics>(entity);
            metrics.font_id = gameContext._runtime->loadFont(gameContext._assetsPath + metrics.fontPath);
        }

        view = registry.view<Console>();
        for (auto entity : view)
        {
            auto &console = view.get<Console>(entity);
            console.font_id = gameContext._runtime->loadFont(gameContext._assetsPath + console.fontPath);
        }
    }

    void update(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Metrics>();
        for (auto entity : view)
        {
            if (gameContext._runtime->getKeyDown(KeyCode::F1))
            {
                auto &metrics = view.get<Metrics>(entity);
                metrics.display = !metrics.display;
            }
        }

        view = registry.view<Console>();
        for (auto entity : view)
        {
            auto &console = view.get<Console>(entity);
            if (gameContext._runtime->getKeyDown(KeyCode::F2))
            {
                console.display = !console.display;
            }
            if (console.display)
            {
                if (gameContext._runtime->getKeyDown(KeyCode::F3))
                {
                    handleInput(console, gameContext);
                    console.history.push_back(console.input);
                    if (console.history.size() > 6)
                        console.history.erase(console.history.begin());
                    console.input = "";
                }
                else if (gameContext._runtime->getKeyDown(KeyCode::Backspace))
                {
                    if (!console.input.empty())
                        console.input.pop_back();
                }
                else if (gameContext._runtime->getKeyDown(KeyCode::Space))
                {
                    console.input += " ";
                }
                else
                {
                    for (int i = 0; i < KeyCodeToChar.size(); i++)
                    {
                        if (gameContext._runtime->getKeyDown((KeyCode)i))
                        {
                            console.input += KeyCodeToChar[i];
                        }
                    }
                }
            }
        }
    }

    void draw(mobs::Registry &registry, GameContext &gameContext) override
    {
        auto view = registry.view<Metrics, Transform>();
        for (auto entity : view)
        {
            if (!view.get<Metrics>(entity).display)
                continue;
            auto &metrics = view.get<Metrics>(entity);
            auto &transform = view.get<Transform>(entity);
            std::string fps = "FPS: " + std::to_string( 1.0f / gameContext._deltaT);
            gameContext._runtime->drawText(metrics.font_id, fps, transform.position, metrics.fontSize, mlg::vec3(255, 255, 255), false);

            std::string cpuUsage = getCPUUsage();
            std::string memoryUsage = getMemoryUsage();

            mlg::vec3 mousePos = gameContext._runtime->getMousePosition();
            std::string mousePosStr = "Mouse Position: (" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")";

            gameContext._runtime->drawText(metrics.font_id, cpuUsage, transform.position + mlg::vec3(0, metrics.fontSize, 0), metrics.fontSize, mlg::vec3(255, 255, 255), false);
            gameContext._runtime->drawText(metrics.font_id, memoryUsage, transform.position + mlg::vec3(0, metrics.fontSize * 2, 0), metrics.fontSize, mlg::vec3(255, 255, 255), false);
            gameContext._runtime->drawText(metrics.font_id, mousePosStr, transform.position + mlg::vec3(0, metrics.fontSize * 3, 0), metrics.fontSize, mlg::vec3(255, 255, 255), false);

            int systemCount = gameContext._systemCount;
            int entityCount = registry.getEntityCount();
            std::string ecsInfo = "Systems Running: " + std::to_string(systemCount) + " Entities Alive: " + std::to_string(entityCount);
            gameContext._runtime->drawText(metrics.font_id, ecsInfo, transform.position + mlg::vec3(0, metrics.fontSize * 4, 0), metrics.fontSize, mlg::vec3(255, 255, 255), false);
        }

        view = registry.view<Console>();
        for (auto entity : view)
        {
            if (!view.get<Console>(entity).display)
                continue;
            auto &console = view.get<Console>(entity);
            auto &transform = view.get<Transform>(entity);
            gameContext._runtime->drawText(console.font_id, std::string("/") + console.input, transform.position, console.fontSize, mlg::vec3(255, 255, 255), false);
            int i = 1;
            for (auto it = console.history.rbegin(); it != console.history.rend(); ++it)
            {
                gameContext._runtime->drawText(console.font_id, *it, transform.position + mlg::vec3(0, console.fontSize * i, 0), console.fontSize, mlg::vec3(255, 255, 255), false);
                i++;
            }
        }
    }

   private:
            std::string getCPUUsage()
        {
#ifdef _WIN32
            FILETIME idleTime, kernelTime, userTime;
            GetSystemTimes(&idleTime, &kernelTime, &userTime);
            return "CPU Usage: [placeholder]";
#else
            std::ifstream file("/proc/stat");
            std::string line;
            std::getline(file, line);
            std::istringstream iss(line);
            std::string cpu;
            long user, nice, system, idle;
            iss >> cpu >> user >> nice >> system >> idle;
            long total = user + nice + system + idle;
            float usage = (total - idle) / (float)total * 100.0f;
            return "CPU Usage: " + std::to_string(usage) + "%";
#endif
        }

        std::string getMemoryUsage()
        {
#ifdef _WIN32
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof(statex);
            GlobalMemoryStatusEx(&statex);
            DWORDLONG totalVirtualMem = statex.ullTotalPageFile;
            DWORDLONG virtualMemUsed = statex.ullTotalPageFile - statex.ullAvailPageFile;
            float memoryUsagePercentage = (virtualMemUsed / (float)totalVirtualMem) * 100.0f;
            return "Memory Usage: " + std::to_string(memoryUsagePercentage) + "%";
#else
            std::ifstream meminfo("/proc/meminfo");
            std::string line;
            long totalMemory = 0, freeMemory = 0, availableMemory = 0;

            while (std::getline(meminfo, line))
            {
                if (line.find("MemTotal:") == 0)
                    std::sscanf(line.c_str(), "MemTotal: %ld kB", &totalMemory);
                else if (line.find("MemFree:") == 0)
                    std::sscanf(line.c_str(), "MemFree: %ld kB", &freeMemory);
                else if (line.find("MemAvailable:") == 0)
                    std::sscanf(line.c_str(), "MemAvailable: %ld kB", &availableMemory);
            }

            long usedMemory = totalMemory - freeMemory;
            float memoryUsagePercentage = (usedMemory / (float)totalMemory) * 100.0f;
            return "Memory Usage: " + std::to_string(memoryUsagePercentage) + "%";
#endif
        }

    private:
        std::string KeyCodeToChar = "abcdefghijklmnopqrstuvwxyz,.t0123456789";

        void handleInput(Console &console, GameContext &gameContext)
        {
            std::istringstream iss(console.input);
            std::string command;
            iss >> command;  // Extract the command

            if (command == "scene") {
                std::string sceneName;
                iss >> sceneName;
                gameContext._sceneManager.switchScene(sceneName);
            } else if (command == "prefab") {
                std::string prefabName;
                iss >> prefabName;

                gameContext._sceneManager.instantiate(prefabName, gameContext);
            } else if (command == "exit") {
                gameContext._running = false;
            } else if (command == "fps") {
                int fps;
                iss >> fps;
                gameContext._clockManager.setTargetDrawDeltaT(1.0f / fps);
            } else if (command == "help") {
                std::cout << "Available commands:" << std::endl;
                std::cout << "/scene [sceneName] - Switch to the specified scene" << std::endl;
                std::cout << "/prefab [prefabName] - Instantiate the specified prefab" << std::endl;
                std::cout << "/exit - Exit the game" << std::endl;
                std::cout << "/fps [fps] - Set the target FPS" << std::endl;
            } else {
                std::cout << "Unknown command: " << command << std::endl;
            }
        }

};

}  // namespace RType

#endif  // ADMINSYSTEM_H