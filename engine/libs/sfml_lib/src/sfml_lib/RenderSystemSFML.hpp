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

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "IRuntime/IRuntime.hpp"

namespace RType
{

class RenderSystemSFML : public RType::IRuntime
{
   public:
    RenderSystemSFML();
    ~RenderSystemSFML();

   public:
    void pollEvents() override;
    bool getKey(KeyCode key) override;
    bool getKeyUp(KeyCode key) override;
    bool getKeyDown(KeyCode key) override;
    void clearWindow() override;
    void updateWindow() override;
    std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath);
    int loadSprite(const std::string& filePath) override;
    void unloadSprite(int spriteId) override;
    void drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale,
                    float rotation) override;
    void drawSprite(int spriteId, mlg::vec3 position) override;
    mlg::vec3 getTextureSize(int spriteId) override;
    mlg::vec3 getMousePosition() override;
    void setGameIcon(const std::string& filePath) override;
    void drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                  unsigned int fontSize, const mlg::vec3& color, bool centered) override;
    void drawRectangle(mlg::vec4& spriteCoords, bool full,
                       const mlg::vec3& color = mlg::vec3(0, 0, 0)) override;
    void FullScreenWindow(bool fullscreen) override;
    bool isWindowOpen() override { return _window.isOpen(); }
    sf::RenderWindow& getWindow() { return this->_window; }
    int loadMusic(const std::string& filePath) override;
    void playMusic(int musicID, bool loop = true) override;
    void stopCurrentMusic() override;
    void unloadMusic(int musicID) override;
    int loadSound(const std::string& filePath) override;
    void playSound(const int soundID) override;
    void unloadSound(const int soundID) override;
    int loadFont(const std::string& filePath) override;
    void setFramerateLimit(unsigned int limit) override;
    void setVerticalSyncEnabled(bool enabled) override;
    int loadShader(const std::string& vertexShaderPath,
                   const std::string& fragmentShaderPath) override;
    void setShader(int shaderId) override;
    void resetShader() override;
    void unloadShader(int shaderId) override;
    void setSoundVolume(int volume) override;

   private:
    sf::Image _icon;
    bool _isFullScreen;
    sf::RenderWindow _window;

    std::unordered_map<int, std::shared_ptr<sf::Sprite>> _spriteCache;
    std::unordered_map<int, std::shared_ptr<sf::Music>> _musics;
    std::unordered_map<int, std::shared_ptr<sf::SoundBuffer>> _sounds;
    std::unordered_map<int, std::shared_ptr<sf::Shader>> _shaders;
    std::unordered_map<int, std::shared_ptr<sf::Font>> _fonts;

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;

    std::map<std::string, int> _musicCache;
    std::map<std::string, int> _soundCache;
    std::map<std::string, int> _fontCache;
    std::map<std::string, int> _shaderCache;

    int _nextSpriteId;
    int _nextShaderId;
    int _nextFontId;
    int _nextMusicId;
    int _nextSoundId;

    sf::Music* _currentMusic = nullptr;
    std::vector<sf::Sound> _activeSounds;

    int _currentMusicId = -1;

    KeyCode convertSFMLKeyToKeyCode(sf::Keyboard::Key key);
    KeyCode convertSFMLMouseToKeyCode(sf::Mouse::Button button);
    KeyCode convertSFMLJoystickButtonToKeyCode(unsigned int button);

    std::unordered_map<int, bool> _currentKeys;
    std::unordered_map<int, bool> _previousKeys;

    int _soundVolume = 50;

    sf::Shader* _activeShader;
};

}  // namespace RType
