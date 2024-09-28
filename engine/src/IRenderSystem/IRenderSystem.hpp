/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

    #include <iostream>
    #include <memory>
    #include "../common/Event.hpp"

/**
 * @file IRenderSystem.hpp
 * @brief Rendering interface for the RType game.
 */

namespace RType
{
    /**
     * @class IRenderSystem
     * @brief Interface for managing the rendering system.
     *
     * This interface defines the necessary methods for any rendering system
     * used in the RType game. Derived classes must implement these methods
     * to handle rendering, user input, and window control.
     */
    class IRenderSystem {

    public:
        /**
         * @brief Pure virtual method to capture user input.
         * @return RType::Event The captured user event.
         *
         * This method must be implemented to capture user input
         * (keyboard, mouse, etc.).
         */
        virtual RType::Event getInput() = 0;

        /**
         * @brief Pure virtual method to clear the window before a new frame.
         *
         * This method must be implemented to clear the window content,
         * preparing it for the next frame to be displayed.
         */
        virtual void clearWindow() = 0;

        /**
         * @brief Pure virtual method to update the window after rendering.
         *
         * Must be implemented to handle displaying content on the screen
         * after all rendering operations are completed.
         */
        virtual void updateWindow() = 0;

        /**
         * @brief Pure virtual method to draw a sprite on the window.
         *
         * This method must be implemented to render images or sprites
         * in the rendering window.
         */
        virtual void drawSprite() = 0;

        /**
         * @brief Pure virtual method to draw text on the window.
         *
         * Must be implemented to handle displaying text (such as scores or information)
         * on the screen.
         */
        virtual void drawText() = 0;

        /**
         * @brief Pure virtual method to toggle fullscreen mode.
         *
         * This method should allow switching the window to fullscreen mode or returning
         * to normal windowed mode.
         */
        virtual void FullScreenWindow() = 0;

        /**
         * @brief Pure virtual method to check if the window is open.
         * @return `true` if the window is currently open, `false` otherwise.
         *
         * This method must be implemented to check whether the window is still open.
         * It is useful for determining if the game should continue running or if the
         * window has been closed, prompting a shutdown of the rendering loop.
         */
        virtual bool isWindowOpen() = 0;

    private:
        // No private member data defined in this interface.
    };
}
