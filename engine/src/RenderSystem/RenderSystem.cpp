/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "RenderSystem.hpp"

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
RenderSystem::RenderSystem() : _window(sf::VideoMode(1920, 1080), "RType"), _isFullScreen(false) {
    // Initialization code here
}

/**
 * @brief Destructor for the RenderSystem.
 * 
 * Cleans up resources and can be used to close the game window when necessary.
 */
RenderSystem::~RenderSystem() {
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
Event RenderSystem::getInput()
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
void RenderSystem::clearWindow()
{
    _window.clear(sf::Color::Black);
}

/**
 * @brief Updates the game window to display the rendered content.
 * 
 * This function refreshes the window to display everything that has been drawn since the last call to clearWindow().
 */
void RenderSystem::updateWindow()
{
    _window.display();
}

/**
 * @brief Toggles between fullscreen and windowed mode.
 * 
 * Switches the window from fullscreen mode to windowed mode (1920x1080) or vice versa.
 * The current state is tracked by the `_isFullScreen` flag.
 */
void RenderSystem::FullScreenWindow()
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
 * @brief Draws a sprite on the game window.
 * 
 * Placeholder function for drawing sprites. It is currently not implemented but intended for future use.
 */
void RenderSystem::drawSprite() {
    // To be implemented
}

/**
 * @brief Draws text on the game window.
 * 
 * Placeholder function for drawing text. It is currently not implemented but intended for future use.
 */
void RenderSystem::drawText() {
    // To be implemented
}

} // namespace RType
