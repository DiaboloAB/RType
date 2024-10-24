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

/**
 * @file RenderSystem.hpp
 * @brief Declaration of the RenderSystem class in the RType namespace.
 */

namespace RType
{

/**
 * @class RenderSystem
 * @brief Rendering system for the RType game.
 *
 * This class manages rendering operations such as window management,
 * displaying sprites, text, and handling graphical interface-related events.
 */
class RenderSystemSFML : public RType::IRuntime
{
   public:
    /**
     * @brief Constructor for the RenderSystem class.
     *
     * Initializes a graphical window with a resolution of 1920x1080 pixels.
     */
    RenderSystemSFML();

    /**
     * @brief Destructor for the RenderSystem class.
     */
    ~RenderSystemSFML();

   public:
    void pollEvents() override;

    /**
     * @brief Checks if a specific key is currently pressed.
     * @param key The key to check.
     * @return `true` if the key is pressed, `false` otherwise.
     */
    bool getKey(KeyCode key) override;

    /**
     * @brief Checks if a specific key was released since the last update.
     * @param key The key to check.
     * @return `true` if the key was released, `false` otherwise.
     */
    bool getKeyUp(KeyCode key) override;

    /**
     * @brief Checks if a specific key was pressed since the last update.
     * @param key The key to check.
     * @return `true` if the key was pressed, `false` otherwise.
     */
    bool getKeyDown(KeyCode key) override;

    /**
     * @brief Clears the window for the next frame rendering.
     *
     * This method should be called before each rendering cycle to clear the window content
     * and prepare it for displaying a new frame.
     */
    void clearWindow() override;

    /**
     * @brief Updates the window after rendering.
     *
     * This method displays the window content after the rendering cycle.
     */
    void updateWindow() override;

    /**
     * @brief Loads a texture from file and stores it in a cache using a shared pointer.
     * If the texture is already loaded, it returns the existing one.
     * @param filePath The file path of the texture to load.
     * @return A shared pointer to the loaded texture.
     */
    std::shared_ptr<sf::Texture> loadTexture(const std::string& filePath);

    /**
     * @brief Loads a sprite using a shared texture and returns its unique ID.
     * @param filePath The file path of the texture to use for the sprite.
     * @return The unique ID of the loaded sprite.
     */
    int loadSprite(const std::string& filePath) override;

    /**
     * @brief Unloads a specific sprite by its ID and decrements reference count.
     * The texture and sprite are automatically deallocated when no more entities use them.
     * @param spriteId The unique ID of the sprite to unload.
     */
    void unloadSprite(int spriteId) override;

    /**
     * @brief Draws a sprite on the window by its ID.
     * @param spriteId The unique ID of the sprite.
     */
    void drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale,
                    float rotation) override;

    /**
     * @brief Draws a sprite on the window by its file path.
     * @param filePath The file path of the sprite's texture.
     */
    void drawSprite(int spriteId, mlg::vec3 position) override;

    /**
     * @brief Retrieves the size of a sprite's texture by its ID.
     * @param spriteId The unique ID of the sprite.
     * @return The size of the texture as a `mlg::vec3`.
     */
    mlg::vec3 getTextureSize(int spriteId) override;

    /**
     * @brief Gets the current position of the mouse cursor.
     * @return The mouse position as a `mlg::vec3`.
     */
    mlg::vec3 getMousePosition() override;

    /**
     * @brief Sets the window icon from a specified image file.
     * @param filePath The file path of the icon image.
     */
    void setGameIcon(const std::string& filePath) override;

    /**
     * @brief Displays text on the screen.
     * @param fontPath The path to the font file.
     * @param textStr The string of text to display.
     * @param position The position to draw the text.
     * @param fontSize The size of the font.
     * @param textColor The color of the text.
     */
    void drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                  unsigned int fontSize, const mlg::vec3& color, bool centered) override;

    /**
     * @brief Draws a rectangle on the window.
     * @param spriteCoords The position and size of the rectangle.
     * @param full If `true`, the rectangle is filled; otherwise, it's outlined.
     * @param textColor The color of the rectangle.
     */
    void drawRectangle(mlg::vec4& spriteCoords, bool full,
                       const mlg::vec3& color = mlg::vec3(0, 0, 0)) override;

    /**
     * @brief Toggles the window to fullscreen mode.
     *
     * Allows switching the window to fullscreen mode or returning to normal windowed mode.
     */
    void FullScreenWindow() override;

    /**
     * @brief Checks if the window is open.
     * @return `true` if the window is open, `false` otherwise.
     */
    bool isWindowOpen() override { return _window.isOpen(); }

    /**
     * @brief Provides access to the SFML render window.
     *
     * This function returns a reference to the rendering window used for drawing in the
     * application.
     * @return sf::RenderWindow& Reference to the SFML window instance used for rendering.
     */
    sf::RenderWindow& getWindow() { return this->_window; }

    /**
     * @brief Preloads a music file and stores it in a cache.
     * @param filePath The file path of the music file to load (e.g.,
     * "assets/music/background.ogg").
     * @return `true` if the music was preloaded successfully, `false` otherwise.
     */
    int loadMusic(const std::string& filePath) override;

    /**
     * @brief Plays a preloaded music.
     * @param musicName The unique name of the preloaded music to play.
     * @param loop Whether the music should loop continuously (default is `true`).
     */
    void playMusic(int musicID, bool loop = true) override;

    /**
     * @brief Stops the currently playing music.
     */
    void stopCurrentMusic() override;

    /**
     * @brief Unloads a specific music from the cache.
     * @param musicName The unique name of the preloaded music to unload.
     */
    void unloadMusic(int musicID) override;

    /**
     * @brief Preloads a sound buffer from a file and stores it in a cache.
     * @param filePath The file path of the sound file to load.
     * @return `true` if the sound was preloaded successfully, `false` otherwise.
     */
    int loadSound(const std::string& filePath) override;

    /**
     * @brief Plays a preloaded sound.
     * @param filePath The file path of the preloaded sound to play.
     */
    void playSound(const int soundID) override;

    /**
     * @brief Unloads a specific sound from the cache.
     * @param soundName The unique name of the preloaded sound to unload.
     */
    void unloadSound(const int soundID) override;

    /**
     * @brief Loads a font from a file.
     * @param filePath The file path of the font to load.
     */
    int loadFont(const std::string& filePath) override;

    void setFramerateLimit(unsigned int limit) override;

    void setVerticalSyncEnabled(bool enabled) override;

    void updateSounds() override;

    int loadShader(const std::string& vertexShaderPath,
                   const std::string& fragmentShaderPath) override;
    void setShader(int shaderId) override;
    void resetShader() override;

   private:
    bool _isFullScreen;
    sf::RenderWindow _window;

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _textures;
    std::unordered_map<int, std::shared_ptr<sf::Sprite>> _spriteCache;

    int _nextSpriteId;

    std::unordered_map<int, std::shared_ptr<sf::Music>> _musics;
    sf::Music* _currentMusic = nullptr;
    std::map<std::string, std::unique_ptr<sf::SoundBuffer>> _soundBuffers;
    std::unordered_map<int, std::shared_ptr<sf::SoundBuffer>> _soundCache;
    std::vector<sf::Sound> _activeSounds;
    int _nextSoundId;

    KeyCode convertSFMLKeyToKeyCode(sf::Keyboard::Key key);
    KeyCode convertSFMLMouseToKeyCode(sf::Mouse::Button button);
    std::unordered_map<int, bool> _currentKeys;
    std::unordered_map<int, bool> _previousKeys;
    sf::Image _icon;
    std::unordered_map<int, std::shared_ptr<sf::Font>> _fonts;
    std::unordered_map<int, std::shared_ptr<sf::Shader>> _shaderCache;
    int _nextShaderId;
    int _nextFontId;
    int _nextMusicId;
    sf::Shader* _activeShader;
};

}  // namespace RType
