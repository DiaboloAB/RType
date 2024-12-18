/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <mlg/mlg.hpp>
#include <string>
#include <vector>

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

    /**
     * @brief Pure virtual method to poll events.
     *
     * This method must be implemented to poll events such as user input
     * or window events.
     */
    virtual void pollEvents() {}

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKey(KeyCode key) { return false; }

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKeyUp(KeyCode key) { return false; }

    /**
     * @brief Pure virtual method to retrieve user input.
     * @return The captured event.
     *
     * This method must be implemented to capture user input events
     * such as keyboard presses, mouse clicks, or other input devices.
     */
    virtual bool getKeyDown(KeyCode key) { return false; }

    /**
     * @brief Pure virtual method to clear the window before a new frame.
     *
     * This method must be implemented to clear the window content,
     * preparing it for the next frame to be displayed.
     */
    virtual void clearWindow() {}

    /**
     * @brief Pure virtual method to update the window after rendering.
     *
     * Must be implemented to handle displaying content on the screen
     * after all rendering operations are completed.
     */
    virtual void updateWindow() {}

    /**
     * @brief Pure virtual method to set the window title.
     * @param title The title to set for the window.
     *
     * This method must be implemented to set the title of the window.
     */
    virtual mlg::vec3 getTextureSize(int spriteId) { return mlg::vec3(0, 0, 0); }

    /**
     * @brief Pure virtual method to set the window title.
     * @param title The title to set for the window.
     *
     * This method must be implemented to set the title of the window.
     */
    virtual mlg::vec3 getMousePosition() { return mlg::vec3(0, 0, 0); }

    /**
     * @brief Pure virtual method to set the window title.
     * @param title The title to set for the window.
     *
     * This method must be implemented to set the title of the window.
     */
    virtual void drawRectangle(mlg::vec4& spriteCoords, bool full,
                               const mlg::vec3& color = mlg::vec3(0, 0, 0)) {}

    /**
     * @brief Pure virtual method to set the window icon.
     * @param filePath The path to the icon file.
     *
     * This method must be implemented to set the icon of the window.
     */
    virtual void setGameIcon(const std::string& filePath) {}

    /**
     * @brief Pure virtual method to set the window title.
     * @param title The title to set for the window.
     *
     * This method must be implemented to set the title of the window.
     */
    virtual int loadFont(const std::string& filePath) { return 0; }

    /**
     * @brief Pure virtual method to load a sprite using a previously loaded texture.
     * @param textureName The name of the texture to use for the sprite.
     *
     * This method must be implemented to assign a texture to a sprite.
     */
    virtual int loadSprite(const std::string& filePath) { return 0; }

    /**
     * @brief Pure virtual method to draw a sprite on the window.
     *
     * This method must be implemented to render images or sprites
     * in the rendering window.
     */
    virtual void drawSprite(int spriteId, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale,
                            float rotation) {}
    virtual void drawSprite(int spriteId, mlg::vec3 position) {}

    /**
     * @brief Pure virtual method to draw text on the window.
     *
     * Must be implemented to handle displaying text (such as scores or information)
     * on the screen.
     */
    virtual void drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                          unsigned int fontSize, const mlg::vec3& color, bool centered) {}

    /**
     * @brief Pure virtual method to toggle fullscreen mode.
     *
     * This method should allow switching the window to fullscreen mode or returning
     * to normal windowed mode.
     */
    virtual void FullScreenWindow(bool fullscreen) {}

    /**
     * @brief Pure virtual method to check if the window is open.
     * @return `true` if the window is currently open, `false` otherwise.
     *
     * This method must be implemented to check whether the window is still open.
     * It is useful for determining if the game should continue running or if the
     * window has been closed, prompting a shutdown of the rendering loop.
     */
    virtual bool isWindowOpen() { return true; }

    /**
     * @brief Pure virtual method to unload a sprite from memory.
     * @param spriteName The name of the sprite to unload.
     *
     * This method must be implemented to remove a sprite from memory.
     */
    virtual void unloadSprite(int spriteId) {}

    /**
     * @brief Pure virtual method to load a music file.
     * @param musicName The name to assign to the music.
     * @param filePath The path to the music file.
     * @return `true` if the music was loaded successfully, `false` otherwise.
     *
     * This method must be implemented to load a music file into memory.
     */
    virtual int loadMusic(const std::string& filePath) { return 0; }

    /**
     * @brief Pure virtual method to play a music file.
     * @param musicName The name of the music to play.
     * @param loop `true` to loop the music, `false` to play it once.
     *
     * This method must be implemented to play a music file that has been loaded
     * into memory.
     */
    virtual void playMusic(int musicID, bool loop = true) {}

    /**
     * @brief Pure virtual method to stop the currently playing music.
     *
     * This method must be implemented to stop the currently playing music.
     */
    virtual void stopCurrentMusic() {}

    /**
     * @brief Pure virtual method to unload a music file from memory.
     * @param musicName The name of the music to unload.
     *
     * This method must be implemented to remove a music file from memory.
     */
    virtual void unloadMusic(int musicID) {}

    /**
     * @brief Pure virtual method to load a sound file.
     * @param soundName The name to assign to the sound.
     * @param filePath The path to the sound file.
     * @return `true` if the sound was loaded successfully, `false` otherwise.
     *
     * This method must be implemented to load a sound file into memory.
     */
    virtual int loadSound(const std::string& filePath) { return 0; }

    /**
     * @brief Pure virtual method to play a sound file.
     * @param soundName The name of the sound to play.
     *
     * This method must be implemented to play a sound file that has been loaded
     * into memory.
     */
    virtual void playSound(const int soundID) {}

    /**
     * @brief Pure virtual method to unload a sound file from memory.
     * @param soundName The name of the sound to unload.
     *
     * This method must be implemented to remove a sound file from memory.
     */
    virtual void unloadSound(const int soundID) {}

    /**
     * @brief Pure virtual method to set the framerate limit.
     * @param limit The framerate limit to set.
     *
     * This method must be implemented to set the maximum framerate for the game.
     */
    virtual void setFramerateLimit(unsigned int limit) {}

    /**
     * @brief Pure virtual method to set the vertical sync.
     * @param enabled `true` to enable vertical sync, `false` to disable it.
     *
     * This method must be implemented to enable or disable vertical sync.
     */
    virtual void setVerticalSyncEnabled(bool enabled) {}

    /**
     * @brief Pure virtual method to load a shader.
     * @param vertexShaderPath The path to the vertex shader file.
     * @param fragmentShaderPath The path to the fragment shader file.
     * @return The ID of the loaded shader.
     *
     * This method must be implemented to load a shader from a vertex and fragment
     * shader file.
     */
    virtual int loadShader(const std::string& vertexShaderPath,
                           const std::string& fragmentShaderPath) { return 0; }

    /**
     * @brief Pure virtual method to set the active shader.
     * @param shaderId The ID of the shader to set as active.
     */
    virtual void setShader(int shaderId) {}

    /**
     * @brief Pure virtual method to reset the active shader.
     *
     * This method must be implemented to reset the active shader to the default
     * shader.
     */
    virtual void resetShader() {}

    /**
     * @brief Pure virtual method to set the sound volume.
     * @param volume The volume level to set.
     *
     * This method must be implemented to set the volume level for sound effects.
     */
    virtual void setSoundVolume(int volume) {}

    /**
     * @brief Pure virtual method to set the music volume.
     * @param volume The volume level to set.
     *
     * This method must be implemented to set the volume level for music.
     */
    virtual void setMusicVolume(int volume) {}

    /**
     * @brief Pure virtual method to load a texture from a file.
     * @param filePath The path to the texture file.
     * @return A shared pointer to the loaded texture.
     *
     * This method must be implemented to load a texture from a file and return
     * a shared pointer to the loaded texture.
     */
    virtual void setMouseCursorVisible(bool visible) {}

    /**
     * @brief Pure virtual method to load a texture from a file.
     * @param filePath The path to the texture file.
     * @return A shared pointer to the loaded texture.
     *
     * This method must be implemented to load a texture from a file and return
     * a shared pointer to the loaded texture.
     */
    virtual void unloadShader(int shaderId) {}

   private:
    // No private member data defined in this interface.
};
}  // namespace RType
