/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once
#include <unistd.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../IRuntime/IRuntime.hpp"

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
     * @brief Loads a texture from file and stores it in a cache.
     * @param textureName The unique name of the texture.
     * @param filePath The file path of the texture to load.
     * @return `true` if the texture was loaded successfully, `false` otherwise.
     */
    bool loadTexture(const std::string& textureName, const std::string& filePath) override;

    /**
     * @brief Unloads a specific texture from the cache.
     * @param textureName The unique name of the texture to unload.
     */
    void unloadTexture(const std::string& textureName) override;

    /**
     * @brief Loads a sprite using a texture from the cache.
     * @param textureName The name of the texture to use for the sprite.
     */
    void loadSprite(const std::string& filePath) override;

    /**
     * @brief Unloads a specific sprite and its associated texture from the cache.
     * @param spriteName The unique name of the sprite to unload.
     */
    void unloadSprite(const std::string& spriteName) override;

    /**
     * @brief Draws a sprite on the window at a specific position, with given coordinates, scale, and rotation.
     * @param spriteName The name of the sprite.
     * @param position The position where the sprite will be drawn.
     * @param spriteCoords The coordinates and size of the sprite within the texture.
     * @param scale The scale to apply to the sprite.
     * @param rotation The rotation to apply to the sprite in degrees.
     */
    void drawSprite(const std::string& spriteName, mlg::vec2 position, mlg::vec4 spriteCoords,
                    mlg::vec2 scale, float rotation) override;

    /**
     * @brief Draws a sprite on the window at a specific position.
     * @param spriteName The name of the sprite.
     * @param position The position where the sprite will be drawn.
     */
    void drawSprite(const std::string& spriteName, mlg::vec2 position) override;

    /**
     * @brief Retrieves the size of a sprite's texture.
     * @param spriteName The name of the sprite.
     * @return The size of the texture as a `mlg::vec2`.
     */
    mlg::vec2 getTextureSize(const std::string& spriteName) override;

    /**
     * @brief Gets the current position of the mouse cursor.
     * @return The mouse position as a `mlg::vec2`.
     */
    mlg::vec2 getMousePosition() override;

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
    void drawText(const std::string& fontPath, const std::string& textStr, const mlg::vec2 position,
                  unsigned int fontSize, const mlg::vec3& textColor) override;

    /**
     * @brief Draws a rectangle on the window.
     * @param spriteCoords The position and size of the rectangle.
     * @param full If `true`, the rectangle is filled; otherwise, it's outlined.
     * @param textColor The color of the rectangle.
     */
    void drawRectangle(mlg::vec4& spriteCoords, bool full, const mlg::vec3& textColor) override;

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
     * This function returns a reference to the rendering window used for drawing in the application.
     * @return sf::RenderWindow& Reference to the SFML window instance used for rendering.
     */
    sf::RenderWindow& getWindow() { return this->_window; }

    /**
     * @brief Preloads a music file and stores it in a cache.
     * @param musicName The unique name used to reference the music.
     * @param filePath The file path of the music file to load (e.g., "assets/music/background.ogg").
     * @return `true` if the music was preloaded successfully, `false` otherwise.
     */
    bool loadMusic(const std::string& musicName, const std::string& filePath) override;

    /**
     * @brief Plays a preloaded music.
     * @param musicName The unique name of the preloaded music to play.
     * @param loop Whether the music should loop continuously (default is `true`).
     */
    void playMusic(const std::string& musicName, bool loop = true) override;

    /**
     * @brief Stops the currently playing music.
     *
     * This function stops the playback of any music currently playing. It does not unload
     * the music from memory.
     */
    void stopCurrentMusic() override;

    /**
     * @brief Unloads a specific music from the cache.
     * @param musicName The unique name of the preloaded music to unload.
     *
     * This function removes a preloaded music from the cache, freeing the memory associated
     * with it. If the music is currently playing, it will be stopped before being unloaded.
     */
    void unloadMusic(const std::string& musicName) override;

    /**
     * @brief Preloads a sound buffer from a file and stores it in a cache.
     * @param soundName The unique name used to reference the sound.
     * @param filePath The file path of the sound file to load.
     * @return `true` if the sound was preloaded successfully, `false` otherwise.
     */
    bool loadSound(const std::string& soundName, const std::string& filePath) override;

    /**
     * @brief Plays a preloaded sound.
     * @param soundName The unique name of the preloaded sound to play.
     */
    void playSound(const std::string& soundName) override;

    /**
     * @brief Unloads a specific sound from the cache.
     * @param soundName The unique name of the preloaded sound to unload.
     *
     * This function removes a preloaded sound from the cache, freeing the memory associated with it.
     */
    void unloadSound(const std::string& soundName) override;

    /**
     * @brief Loads a font from a file.
     * @param filePath The file path of the font to load.
     */
    void loadFont(const std::string& filePath) override;

   private:
    bool _isFullScreen;
    sf::RenderWindow _window;
    std::map<std::string, std::unique_ptr<sf::Texture>> _textures;
    std::map<std::string, sf::Sprite> _sprites;
    std::map<std::string, std::unique_ptr<sf::Music>> _musics;
    sf::Music* _currentMusic = nullptr;
    std::map<std::string, std::unique_ptr<sf::SoundBuffer>> _soundBuffers;
    std::vector<sf::Sound> _sounds;

    KeyCode convertSFMLKeyToKeyCode(sf::Keyboard::Key key);
    KeyCode convertSFMLMouseToKeyCode(sf::Mouse::Button button);
    std::unordered_map<int, bool> _currentKeys;
    std::unordered_map<int, bool> _previousKeys;
    sf::Image _icon;
    std::map<std::string, sf::Font> _fonts;
};
}  // namespace RType
