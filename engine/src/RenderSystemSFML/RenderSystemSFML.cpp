/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystemSFML.hpp"

/**
 * @namespace RType
 * @brief Contains all game systems and components related to the RType game.
 */
namespace RType
{

/**
 * @brief Constructor for the RenderSystem.
 *
 * Initializes the game window with a resolution of 1920x1080 in windowed mode by default.
 * The window will be used to render all graphical content.
 */
RenderSystemSFML::RenderSystemSFML()
    : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false)
{
    // Initialization code here
}

/**
 * @brief Destructor for the RenderSystem.
 *
 * Cleans up resources and can be used to close the game window when necessary.
 */
RenderSystemSFML::~RenderSystemSFML()
{
    // Release resources if needed (e.g., _window.close() if needed)
}

void RenderSystemSFML::pollEvents()
{
    _previousKeys = _currentKeys;
    sf::Event event = {};
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _currentKeys[KeyCode::Close] = true;
        }
        if (event.type == sf::Event::KeyPressed)
        {
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = true;
        }
        if (event.type == sf::Event::KeyReleased)
        {
            _currentKeys[convertSFMLKeyToKeyCode(event.key.code)] = false;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = true;
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            _currentKeys[convertSFMLMouseToKeyCode(event.mouseButton.button)] = false;
        }
    }
}

bool RenderSystemSFML::getKey(KeyCode key)
{
    auto it = _currentKeys.find(static_cast<int>(key));
    if (it != _currentKeys.end())
    {
        return it->second;
    }
    return false;
}

bool RenderSystemSFML::getKeyUp(KeyCode key)
{
    auto it = _previousKeys.find(static_cast<int>(key));
    if (it != _previousKeys.end())
    {
        return it->second;
    }
    return false;
}

bool RenderSystemSFML::getKeyDown(KeyCode key)
{
    auto it = _currentKeys.find(static_cast<int>(key));
    if (it != _currentKeys.end())
    {
        return it->second;
    }
    return false;
}

/**
 * @brief Clears the game window by filling it with a black background.
 *
 * This function is called before drawing new objects or frames, resetting the window to a black
 * screen.
 */
void RenderSystemSFML::clearWindow() { _window.clear(sf::Color::Black); }

/**
 * @brief Updates the game window to display the rendered content.
 *
 * This function refreshes the window to display everything that has been drawn since the last call
 * to clearWindow().
 */
void RenderSystemSFML::updateWindow() { _window.display(); }

/**
 * @brief Toggles between fullscreen and windowed mode.
 *
 * Switches the window from fullscreen mode to windowed mode (1920x1080) or vice versa.
 * The current state is tracked by the `_isFullScreen` flag.
 */
void RenderSystemSFML::FullScreenWindow()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    if (_isFullScreen)
    {
        // Switch to windowed mode
        _window.create(sf::VideoMode(1920, 1080), "RType", sf::Style::Default);
        _isFullScreen = false;
    }
    else
    {
        // Switch to fullscreen mode
        _window.create(fullscreenMode, "RType", sf::Style::Fullscreen);
        _isFullScreen = true;
    }
}

/**
 * @brief Loads a texture from file and stores it in a cache.
 * @param textureName The unique name of the texture.
 * @param filePath The file path of the texture to load.
 * @return `true` if the texture was loaded successfully, `false` otherwise.
 */
bool RenderSystemSFML::loadTexture(const std::string& textureName, const std::string& filePath)
{
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la texture : " << filePath << std::endl;
        return false;
    }
    _textures[textureName] = std::move(texture);
    return true;
}

/**
 * @brief Unloads a specific texture from the cache.
 * @param textureName The unique name of the texture to unload.
 */
void RenderSystemSFML::unloadTexture(const std::string& textureName)
{
    auto it = _textures.find(textureName);
    if (it != _textures.end())
    {
        _textures.erase(it);
    }
}

/**
 * @brief Loads a sprite using a texture from the cache.
 * @param textureName The name of the texture to use for the sprite.
 */
void RenderSystemSFML::loadSprite(const std::string& filePath)
{
    if (loadTexture(filePath, filePath) == false)
    {
        return;
    }
    auto it = _textures.find(filePath);
    if (it != _textures.end())
    {
        sf::Sprite sprite;
        sprite.setTexture(*it->second);
        _sprites[filePath] = sprite;
    }
    else
    {
        std::cerr << "Erreur : texture non trouvée (" << filePath << ")" << std::endl;
    }
}

/**
 * @brief Unloads a specific sprite and its associated texture from the cache.
 * @param spriteName The unique name of the sprite to unload.
 */
void RenderSystemSFML::unloadSprite(const std::string& spriteName)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        _sprites.erase(it);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

/**
 * @brief Draws a sprite from a spritesheet on the game window at the given coordinates.
 *
 * @param spriteName The unique name of the sprite.
 * @param x The x-coordinate where the sprite will be drawn.
 * @param y The y-coordinate where the sprite will be drawn.
 * @param spriteRect The rectangle representing the portion of the spritesheet to use.
 */
void RenderSystemSFML::drawSprite(const std::string& spriteName, mlg::vec2 position,
                                    mlg::vec4 spriteCoords, mlg::vec2 scale, float rotation)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        sf::IntRect spriteRect(spriteCoords.x, spriteCoords.y, spriteCoords.z, spriteCoords.w);
        it->second.setTextureRect(spriteRect);
        it->second.setPosition(position.x, position.y);
        it->second.setScale(scale.x, scale.y);
        it->second.setRotation(rotation);
        _window.draw(it->second);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

void RenderSystemSFML::drawSprite(const std::string& spriteName, mlg::vec2 position)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        it->second.setPosition(position.x, position.y);
        _window.draw(it->second);
    }
    else
    {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

/**
 * @brief Draws text on the game window.
 *
 * Placeholder function for drawing text. It is currently not implemented but intended for future
 * use.
 */
void RenderSystemSFML::drawText()
{
    // To be implemented
}

/**
 * @brief Preloads a music file and stores it in a cache.
 *
 * @param musicName The unique name of the music.
 * @param filePath The file path of the music to load.
 * @return `true` if the music was preloaded successfully, `false` otherwise.
 */
bool RenderSystemSFML::loadMusic(const std::string& musicName, const std::string& filePath)
{
    if (_musics.find(musicName) != _musics.end())
    {
        return true;
    }

    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement de la musique : " << filePath << std::endl;
        return false;
    }

    _musics[musicName] = std::move(music);
    return true;
}

/**
 * @brief Plays a preloaded music.
 *
 * @param musicName The unique name of the music to play.
 * @param loop Whether to loop the music (default is `true`).
 */
void RenderSystemSFML::playMusic(const std::string& musicName, bool loop)
{
    if (_currentMusic != nullptr)
    {
        _currentMusic->stop();
    }

    auto it = _musics.find(musicName);
    if (it != _musics.end())
    {
        _currentMusic = it->second.get();
        _currentMusic->setLoop(loop);
        _currentMusic->play();
    }
    else
    {
        std::cerr << "Erreur : musique non trouvée (" << musicName << ")" << std::endl;
    }
}

/**
 * @brief Stops the currently playing music.
 */
void RenderSystemSFML::stopCurrentMusic()
{
    if (_currentMusic != nullptr)
    {
        _currentMusic->stop();
        _currentMusic = nullptr;
    }
}

/**
 * @brief Unloads a specific music from the cache.
 *
 * @param musicName The unique name of the music to unload.
 */
void RenderSystemSFML::unloadMusic(const std::string& musicName)
{
    auto it = _musics.find(musicName);
    if (it != _musics.end())
    {
        if (_currentMusic == it->second.get())
        {
            _currentMusic->stop();
            _currentMusic = nullptr;
        }
        _musics.erase(it);
    }
}

/**
 * @brief Preloads a sound buffer from file and stores it in a cache.
 *
 * @param soundName The unique name used to reference the sound.
 * @param filePath The file path of the sound file to load (e.g., "assets/sounds/explosion.wav").
 * @return `true` if the sound was preloaded successfully, `false` otherwise.
 */
bool RenderSystemSFML::loadSound(const std::string& soundName, const std::string& filePath)
{
    if (_soundBuffers.find(soundName) != _soundBuffers.end())
    {
        return true;
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filePath))
    {
        std::cerr << "Erreur lors du chargement du son : " << filePath << std::endl;
        return false;
    }

    _soundBuffers[soundName] = std::move(buffer);
    return true;
}

/**
 * @brief Plays a preloaded sound.
 *
 * @param soundName The unique name of the preloaded sound to play.
 */
void RenderSystemSFML::playSound(const std::string& soundName)
{
    auto it = _soundBuffers.find(soundName);
    if (it != _soundBuffers.end())
    {
        sf::Sound sound;
        sound.setBuffer(*it->second);
        _sounds.push_back(sound);
        _sounds.back().play();
    }
    else
    {
        std::cerr << "Erreur : son non trouvé (" << soundName << ")" << std::endl;
    }
}

/**
 * @brief Unloads a specific sound from the cache.
 *
 * @param soundName The unique name of the preloaded sound to unload.
 */
void RenderSystemSFML::unloadSound(const std::string& soundName)
{
    auto it = _soundBuffers.find(soundName);
    if (it != _soundBuffers.end())
    {
        _soundBuffers.erase(it);  // Remove the sound buffer from the cache
    }
}

KeyCode RenderSystemSFML::convertSFMLKeyToKeyCode(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::A:
            return KeyCode::A;
        case sf::Keyboard::B:
            return KeyCode::B;
        case sf::Keyboard::C:
            return KeyCode::C;
        case sf::Keyboard::D:
            return KeyCode::D;
        case sf::Keyboard::E:
            return KeyCode::E;
        case sf::Keyboard::F:
            return KeyCode::F;
        case sf::Keyboard::G:
            return KeyCode::G;
        case sf::Keyboard::H:
            return KeyCode::H;
        case sf::Keyboard::I:
            return KeyCode::I;
        case sf::Keyboard::J:
            return KeyCode::J;
        case sf::Keyboard::K:
            return KeyCode::K;
        case sf::Keyboard::L:
            return KeyCode::L;
        case sf::Keyboard::M:
            return KeyCode::M;
        case sf::Keyboard::N:
            return KeyCode::N;
        case sf::Keyboard::O:
            return KeyCode::O;
        case sf::Keyboard::P:
            return KeyCode::P;
        case sf::Keyboard::Q:
            return KeyCode::Q;
        case sf::Keyboard::R:
            return KeyCode::R;
        case sf::Keyboard::S:
            return KeyCode::S;
        case sf::Keyboard::T:
            return KeyCode::T;
        case sf::Keyboard::U:
            return KeyCode::U;
        case sf::Keyboard::V:
            return KeyCode::V;
        case sf::Keyboard::W:
            return KeyCode::W;
        case sf::Keyboard::X:
            return KeyCode::X;
        case sf::Keyboard::Y:
            return KeyCode::Y;
        case sf::Keyboard::Z:
            return KeyCode::Z;
        case sf::Keyboard::Up:
            return KeyCode::UpArrow;
        case sf::Keyboard::Down:
            return KeyCode::DownArrow;
        case sf::Keyboard::Left:
            return KeyCode::LeftArrow;
        case sf::Keyboard::Right:
            return KeyCode::RightArrow;
        case sf::Keyboard::Escape:
            return KeyCode::Escape;
        case sf::Keyboard::Space:
            return KeyCode::Space;
        case sf::Keyboard::Enter:
            return KeyCode::Enter;
        case sf::Keyboard::Backspace:
            return KeyCode::Backspace;
        case sf::Keyboard::Tab:
            return KeyCode::Tab;
        case sf::Keyboard::Num0:
            return KeyCode::Alpha0;
        case sf::Keyboard::Num1:
            return KeyCode::Alpha1;
        case sf::Keyboard::Num2:
            return KeyCode::Alpha2;
        case sf::Keyboard::Num3:
            return KeyCode::Alpha3;
        case sf::Keyboard::Num4:
            return KeyCode::Alpha4;
        case sf::Keyboard::Num5:
            return KeyCode::Alpha5;
        case sf::Keyboard::Num6:
            return KeyCode::Alpha6;
        case sf::Keyboard::Num7:
            return KeyCode::Alpha7;
        case sf::Keyboard::Num8:
            return KeyCode::Alpha8;
        case sf::Keyboard::Num9:
            return KeyCode::Alpha9;
        default:
            return KeyCode::None;  // Default case, adjust as needed
    }
}

KeyCode RenderSystemSFML::convertSFMLMouseToKeyCode(sf::Mouse::Button button)
{
    switch (button)
    {
        case sf::Mouse::Left:
            return KeyCode::Mouse0;
        case sf::Mouse::Right:
            return KeyCode::Mouse2;
        case sf::Mouse::Middle:
            return KeyCode::Mouse3;
        case sf::Mouse::XButton1:
            return KeyCode::Mouse4;
        case sf::Mouse::XButton2:
            return KeyCode::Mouse5;
        default:
            return KeyCode::None;  // Default case, adjust as needed
    }
}

mlg::vec2 RenderSystemSFML::getMousePosition()
{
    sf::Vector2i position = sf::Mouse::getPosition(_window);
    return mlg::vec2(position.x, position.y, 0);
}

mlg::vec2 RenderSystemSFML::getTextureSize(const std::string& spriteName)
{
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end())
    {
        auto size = it->second.getTexture()->getSize();
        return mlg::vec2(size.x, size.y, 0);
    }
    return mlg::vec2(0, 0, 0);
}

}  // namespace RType
