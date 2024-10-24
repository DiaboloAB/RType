/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NULLRUNTIME_H
#define NULLRUNTIME_H

#include "IRuntime/IRuntime.hpp"
// std

namespace RType
{

class NullRuntime : public IRuntime
{
   public:
    NullRuntime() {}
    ~NullRuntime() {}

    void pollEvents() override {}
    bool getKey(KeyCode key) override { return false; }
    bool getKeyUp(KeyCode key) override { return false; }
    bool getKeyDown(KeyCode key) override { return false; }
    void clearWindow() override {}
    void updateWindow() override {}
    mlg::vec3 getTextureSize(int spriteId) override { return mlg::vec3(0, 0, 0); }
    mlg::vec3 getMousePosition() override { return mlg::vec3(0, 0, 0); }
    void drawRectangle(mlg::vec4& spriteCoords, bool full,
                       const mlg::vec3& color = mlg::vec3(0, 0, 0)) override
    {
    }
    void setGameIcon(const std::string& filePath) override {}
    int loadFont(const std::string& filePath) override { return 0; }
    int loadSprite(const std::string& filePath) override { return 0; }
    void drawSprite(int IDSprite, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale,
                    float rotation) override
    {
    }
    void drawSprite(int IDSprite, mlg::vec3 position) override {}
    void drawText(int fontID, const std::string& textStr, const mlg::vec3 position,
                  unsigned int fontSize, const mlg::vec3& color = mlg::vec3(0, 0, 0),
                  bool centered = false) override
    {
    }
    void FullScreenWindow() override {}
    bool isWindowOpen() override { return true; }
    void unloadSprite(int spriteId) override {}
    int loadMusic(const std::string& filePath) override { return 0; }
    void playMusic(int musicID, bool loop) override { return; }
    void stopCurrentMusic() override {}
    void unloadMusic(int musicID) override {}
    int loadSound(const std::string& filePath) override { return false; }
    void playSound(const int soundID) override {}
    void unloadSound(const int soundID) override {}
    void setFramerateLimit(unsigned int limit) override {}
    void setVerticalSyncEnabled(bool enabled) override {}
    void updateSounds() override {}
    int loadShader(const std::string& vertexShaderPath,
                   const std::string& fragmentShaderPath) override
    {
        return 0;
    }
    void setShader(int shaderId) {}
    void resetShader() {}

   private:
    // Member variables
};

}  // namespace RType

#endif  // NULLRUNTIME_H