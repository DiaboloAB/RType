/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once
#ifdef _WIN32
#include <io.h>
#include <process.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>
#include "IRuntime/IRuntime.hpp"

namespace RType {

class RenderSystemSDL : public RType::IRuntime {
public:
    RenderSystemSDL();
    ~RenderSystemSDL();

    void pollEvents() override;
    bool getKey(KeyCode key) override;
    bool getKeyUp(KeyCode key) override;
    bool getKeyDown(KeyCode key) override;

    void clearWindow() override;
    void updateWindow() override;
    void FullScreenWindow() override;
    bool isWindowOpen() override { return _window != nullptr; }

    std::shared_ptr<SDL_Texture> loadTexture(const std::string& filePath);
    int loadSprite(const std::string& filePath) override;
    void unloadSprite(int spriteId) override;
    void drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale, float rotation) override;
    void drawSprite(int spriteId, mlg::vec3 position) override;
    mlg::vec3 getTextureSize(int spriteId) override;

    int loadFont(const std::string& filePath) override;
    void drawText(int fontID, const std::string& textStr, const mlg::vec3 position, unsigned int fontSize, const mlg::vec3& color, bool centered) override;
    void drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& color = mlg::vec3(0, 0, 0)) override;
    void unloadFont(int fontID);

    int loadMusic(const std::string& filePath) override;
    void playMusic(int musicID, bool loop = true) override;
    void stopCurrentMusic() override;
    void unloadMusic(int musicID) override;

    int loadSound(const std::string& filePath) override;
    void playSound(const int soundID) override;
    void unloadSound(const int soundID) override;

    mlg::vec3 getMousePosition() override;
    void setGameIcon(const std::string& filePath) override;
    void setFramerateLimit(unsigned int limit) override;
    void setVerticalSyncEnabled(bool enabled) override;
    void updateSounds() override;

    int loadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) override;
    void setShader(int shaderId) override;
    void resetShader() override;
    void unloadShader(int shaderId) override;

private:
    bool _isFullScreen;
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> _textures;
    std::unordered_map<int, std::shared_ptr<SDL_Texture>> _spriteCache;
    std::unordered_map<int, std::shared_ptr<Mix_Music>> _musics;
    std::unordered_map<int, std::shared_ptr<Mix_Chunk>> _soundCache;
    std::unordered_map<int, std::shared_ptr<TTF_Font>> _fonts;

    int _nextSpriteId;
    int _nextFontId;
    int _nextMusicId;
    int _nextSoundId;

    Mix_Music* _currentMusic = nullptr;
    std::vector<Mix_Chunk*> _activeSounds;
    std::unordered_map<int, bool> _currentKeys;
    std::unordered_map<int, bool> _previousKeys;

    KeyCode convertSDLKeyToKeyCode(SDL_Keycode key);
    KeyCode convertSDLMouseToKeyCode(Uint8 button);
};

} // namespace RType
