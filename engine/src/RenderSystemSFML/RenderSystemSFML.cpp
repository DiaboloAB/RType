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
namespace RType {

/**
 * @brief Constructor for the RenderSystem.
 * 
 * Initializes the game window with a resolution of 1920x1080 in windowed mode by default.
 * The window will be used to render all graphical content.
 */
RenderSystemSFML::RenderSystemSFML() : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false) {
    // Initialization code here
}

/**
 * @brief Destructor for the RenderSystem.
 * 
 * Cleans up resources and can be used to close the game window when necessary.
 */
RenderSystemSFML::~RenderSystemSFML() {
    // Release resources if needed (e.g., _window.close() if needed)
}

/**
 * @brief Captures and processes user input events.
 * 
 * This function polls events from the SFML window and translates key presses
 * into internal game-specific events. It captures keyboard events such as movement,
 * actions, and special keys like ESC or fullscreen toggle.
 * 
 * @return An `Event` enum value corresponding to the key pressed, such as `Event::ENTER`, `Event::MENU`, or `Event::NONE`.
 */
Event RenderSystemSFML::getInput()
{
    sf::Event event = {};

    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return (Event::ESCAPE);
        if (event.type != sf::Event::KeyPressed)
            continue;
        switch (event.key.code) {
            case sf::Keyboard::F6:
                return (Event::MENU);
            case sf::Keyboard::Enter:
                return (Event::ENTER);
            case sf::Keyboard::Space:
                return (Event::SPACE);
            case sf::Keyboard::Up:
                return (Event::GAME_UP);
            case sf::Keyboard::Down:
                return (Event::GAME_DOWN);
            case sf::Keyboard::Left:
                return (Event::GAME_LEFT);
            case sf::Keyboard::Right:
                return (Event::GAME_RIGHT);
            case sf::Keyboard::Escape:
                return (Event::ESCAPE);
            case sf::Keyboard::Backspace:
                return (Event::BACKSPACE);
            case sf::Keyboard::F11:
                return (Event::FULLSCREEN);
            // Add more key mappings as needed
            default:
                break;
        }
    }
    return NONE;
}

/**
 * @brief Clears the game window by filling it with a black background.
 * 
 * This function is called before drawing new objects or frames, resetting the window to a black screen.
 */
void RenderSystemSFML::clearWindow()
{
    _window.clear(sf::Color::Black);
}

/**
 * @brief Updates the game window to display the rendered content.
 * 
 * This function refreshes the window to display everything that has been drawn since the last call to clearWindow().
 */
void RenderSystemSFML::updateWindow()
{
    _window.display();
}

/**
 * @brief Toggles between fullscreen and windowed mode.
 * 
 * Switches the window from fullscreen mode to windowed mode (1920x1080) or vice versa.
 * The current state is tracked by the `_isFullScreen` flag.
 */
void RenderSystemSFML::FullScreenWindow()
{
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    if (_isFullScreen) {
        // Switch to windowed mode
        _window.create(sf::VideoMode(1920, 1080), "RType", sf::Style::Default);
        _isFullScreen = false;
    } else {
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
bool RenderSystemSFML::loadTexture(const std::string& textureName, const std::string& filePath) {
    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath)) {
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
void RenderSystemSFML::unloadTexture(const std::string& textureName) {
    auto it = _textures.find(textureName);
    if (it != _textures.end()) {
        _textures.erase(it); // Libère la mémoire associée à la texture
    }
}

/**
 * @brief Loads a sprite using a texture from the cache.
 * @param textureName The name of the texture to use for the sprite.
 */
void RenderSystemSFML::loadSprite(const std::string& spriteName, const std::string& textureName) {
    auto it = _textures.find(textureName);
    if (it != _textures.end()) {
        sf::Sprite sprite;
        sprite.setTexture(*it->second);
        _sprites[spriteName] = sprite;  // Ajoute le sprite à la map avec son nom unique
    } else {
        std::cerr << "Erreur : texture non trouvée (" << textureName << ")" << std::endl;
    }
}

/**
 * @brief Draws a sprite on the game window.
 * 
 * Placeholder function for drawing sprites. It is currently not implemented but intended for future use.
 */
void RenderSystemSFML::drawSprite(const std::string& spriteName, float x, float y) {
    auto it = _sprites.find(spriteName);
    if (it != _sprites.end()) {
        // Met à jour la position du sprite
        it->second.setPosition(x, y);
        
        // Dessine le sprite avec la nouvelle position
        _window.draw(it->second);
    } else {
        std::cerr << "Erreur : sprite non trouvé (" << spriteName << ")" << std::endl;
    }
}

/**
 * @brief Draws text on the game window.
 * 
 * Placeholder function for drawing text. It is currently not implemented but intended for future use.
 */
void RenderSystemSFML::drawText() {
    // To be implemented    
}

} // namespace RType
