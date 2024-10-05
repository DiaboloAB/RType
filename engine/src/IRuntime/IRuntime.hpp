/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <mlg/mlg.hpp>

#include "../common/KeyCode.hpp"

/**
 * @file IRuntime.hpp
 * @brief Rendering interface for the RType game.
 */

namespace RType
{
/**
 * @class IRuntime
 * @brief Interface for managing the rendering system.
 *
 * This interface defines the necessary methods for any rendering system
 * used in the RType game. Derived classes must implement these methods
 * to handle rendering, user input, and window control.
 */
class IRuntime
{
   public:
    virtual ~IRuntime() = default;

    virtual void pollEvents() = 0;

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKey(KeyCode key) = 0;

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKeyUp(KeyCode key) = 0;

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKeyDown(KeyCode key) = 0;

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

    virtual mlg::vec2 getTextureSize(const std::string& spriteName) = 0;

    virtual mlg::vec2 getMousePosition() = 0;

    virtual void setGameIcon(const std::string& filePath) = 0;

    /**
     * @brief Pure virtual method to load a sprite using a previously loaded texture.
     * @param textureName The name of the texture to use for the sprite.
     *
     * This method must be implemented to assign a texture to a sprite.
     */
    virtual void loadSprite(const std::string& filePath) = 0;

    /**
     * @brief Unloads a specific sprite and its associated texture from the cache.
     * @param spriteName The unique name of the sprite to unload.
     */
    virtual void unloadSprite(const std::string& spriteName) = 0;

    /**
     * @brief Pure virtual method to draw a sprite on the window.
     *
     * This method must be implemented to render images or sprites
     * in the rendering window.
     */
    virtual void drawSprite(const std::string& spriteName, mlg::vec2 position,
                            mlg::vec4 spriteRect,
                            mlg::vec2 scale,
                            float rotation
                            ) = 0;

    virtual void drawSprite(const std::string& spriteName, mlg::vec2 position) = 0;

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
}  // namespace RType
