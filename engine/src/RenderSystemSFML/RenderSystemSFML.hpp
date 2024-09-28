/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once
    #include <iostream>
    #include <memory>
    #include "../IRenderSystem/IRenderSystem.hpp"
    #include <unistd.h>
    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

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
    class RenderSystemSFML : public RType::IRenderSystem {
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

        /**
         * @brief Retrieves user inputs (keyboard, mouse, etc.).
         * @return RType::Event The captured event.
         *
         * This method captures events coming from the user, such as keyboard inputs or mouse movements.
         */
        RType::Event getInput() override;

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
         * @brief Displays text on the screen.
         *
         * This method allows drawing text on the rendering window.
         */
        void drawText() override;

        /**
         * @brief Displays a sprite on the screen.
         *
         * This method allows drawing a sprite (2D image) on the rendering window.
         */
        void drawSprite() override;

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
     * 
     * @return sf::RenderWindow& Référence à l'instance de la fenêtre SFML utilisée pour le rendu.
     *
     */

        sf::RenderWindow& getWindow() { return this->_window; }

        
    private:
        bool _isFullScreen;        ///< Indicates whether the window is in fullscreen mode.
        sf::RenderWindow _window;  ///< SFML render window.
    };
}
