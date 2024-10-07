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
     * @brief Retrieves user inputs (keyboard, mouse, etc.).
     * @return RType::Event The captured event.
     *
     * This method captures events coming from the user, such as keyboard inputs or mouse movements.
     */
    bool getKey(KeyCode key) override;

    /**
     * @brief Retrieves user inputs (keyboard, mouse, etc.).
     * @return RType::Event The captured event.
     *
     * This method captures events coming from the user, such as keyboard inputs or mouse movements.
     */
    bool getKeyUp(KeyCode key) override;

    /**
     * @brief Retrieves user inputs (keyboard, mouse, etc.).
     * @return RType::Event The captured event.
     *
     * This method captures events coming from the user, such as keyboard inputs or mouse movements.
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
    bool loadTexture(const std::string& textureName, const std::string& filePath);

    /**
     * @brief Unloads a specific texture from the cache.
     * @param textureName The unique name of the texture to unload.
     */
    void unloadTexture(const std::string& textureName);

    /**
     * @brief Loads a sprite using a texture from the cache.
     * @param textureName The name of the texture to use for the sprite.
     */
    void loadSprite(const std::string& filePath) override;

    /**
     * @brief Unloads a specific sprite and its associated texture from the cache.
     * @param spriteName The unique name of the sprite to unload.
     */
    void unloadSprite(const std::string& spriteName);

    /**
     * @brief Draws a sprite on the window.
     */
    void drawSprite(const std::string& spriteName, mlg::vec2 position, mlg::vec4 spriteCoords,
                    mlg::vec2 scale, float rotation) override;

    void drawSprite(const std::string& spriteName, mlg::vec2 position) override;

    mlg::vec2 getTextureSize(const std::string& spriteName) override;

    mlg::vec2 getMousePosition() override;

    void setGameIcon(const std::string& filePath) override;

    /**
     * @brief Displays text on the screen.
     *
     * This method allows drawing text on the rendering window.
     */
    void drawText() override;

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
     * @brief Accède à la fenêtre de rendu SFML.
     *
     * Cette fonction retourne une référence à la fenêtre de rendu utilisée
     * pour dessiner dans l'application.
     *
     * @return sf::RenderWindow& Référence à l'instance de la fenêtre SFML utilisée pour le rendu.
     */
    sf::RenderWindow& getWindow() { return this->_window; }

    /**
     * @brief Preloads a music file and stores it in a cache.
     *
     * This function loads a music
     *
     * @param musicName The unique name used to reference the music.
     * @param filePath The file path of the music file to load (e.g.,
     * "assets/music/background.ogg").
     * @return `true` if the music was preloaded successfully, `false` otherwise.
     */
    bool loadMusic(const std::string& musicName, const std::string& filePath);

    /**
     * @brief Plays a preloaded music.
     *
     * This function plays a music file that has already been preloaded
     *
     * @param musicName The unique name of the preloaded music to play.
     * @param loop Whether the music should loop continuously (default is `true`).
     */
    void playMusic(const std::string& musicName, bool loop = true);

    /**
     * @brief Stops the currently playing music.
     *
     * This function stops the playback of any music currently playing. It does not unload
     * the music from memory.
     */
    void stopCurrentMusic();

    /**
     * @brief Unloads a specific music from the cache.
     *
     * This function removes a preloaded music from the cache, freeing the memory associated
     * with it. If the music is currently playing, it will be stopped before being unloaded.
     *
     * @param musicName The unique name of the preloaded music to unload.
     */
    void unloadMusic(const std::string& musicName);

    /**
     * @brief Preloads a sound buffer from file and stores it in a cache.
     *
     * This function loads a sound
     *
     * @return `true` if the sound was preloaded successfully, `false` otherwise.
     */
    bool loadSound(const std::string& soundName, const std::string& filePath);

    /**
     * @brief Plays a preloaded sound.
     *
     * This function plays a sound
     *
     * @param soundName The unique name of the preloaded sound to play.
     */
    void playSound(const std::string& soundName);

    /**
     * @brief Unloads a specific sound from the cache.
     *
     * This function removes a preloaded sound from the cache
     *
     * @param soundName The unique name of the preloaded sound to unload.
     */
    void unloadSound(const std::string& soundName);

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
};
}  // namespace RType
