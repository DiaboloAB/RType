/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include "../IRuntime/IRuntime.hpp"

/**
 * @file RenderSystemSDL.hpp
 * @brief Declaration of the RenderSystemSDL class in the RType namespace.
 */

namespace RType
{

/**
 * @class RenderSystemSDL
 * @brief SDL-based rendering system for the RType game.
 *
 * This class manages rendering operations such as window management,
 * displaying sprites, text, and handling graphical interface-related events
 * using SDL.
 */
class RenderSystemSDL : public RType::IRuntime
{
   public:
    RenderSystemSDL();
    ~RenderSystemSDL();

    void pollEvents() override;
    bool getKey(KeyCode key) override;
    bool getKeyUp(KeyCode key) override;
    bool getKeyDown(KeyCode key) override;
    void clearWindow() override;
    void updateWindow() override;
    mlg::vec3 getTextureSize(int id) override;
    mlg::vec3 getMousePosition() override;
    void drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color = mlg::vec3(0, 0, 0)) override;
    void setGameIcon(const std::string& filePath) override;
    void loadFont(const std::string& filePath) override;
    int loadSprite(const std::string& filePath) override;
    void drawSprite(int id, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale, float rotation) override;
    void drawSprite(int id, mlg::vec3 position) override;
    void drawText(const std::string& fontPath, const std::string& textStr, const mlg::vec3 position,
                  unsigned int fontSize, const mlg::vec3& color = mlg::vec3(0, 0, 0), bool centered = false) override;
    void FullScreenWindow() override;
    bool isWindowOpen() override;
    void unloadSprite(int id) override;
    bool loadMusic(const std::string& filePath) override;
    void playMusic(const std::string& filePath, bool loop = true) override;
    void stopCurrentMusic() override;
    void unloadMusic(const std::string& filePath) override;
    int loadSound(const std::string& filePath) override;
    void playSound(int id) override;
    void unloadSound(int id) override;
    void setFramerateLimit(unsigned int limit) override;
    void setVerticalSyncEnabled(bool enabled) override;

    // Shader management
    int loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) override;
    void setShader(int shaderId) override;
    void resetShader() override;

   private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool windowOpen;
    std::unordered_map<int, std::shared_ptr<SDL_Texture>> textures;
    std::unordered_map<int, std::shared_ptr<Mix_Chunk>> soundEffects;
    TTF_Font* currentFont;
    Mix_Music* currentMusic;
    std::unordered_map<int, std::string> shaders;
    int currentShaderId;
    bool shaderActive;
    int currentId = 0;
    int generateUniqueId();
};
}  // namespace RType
