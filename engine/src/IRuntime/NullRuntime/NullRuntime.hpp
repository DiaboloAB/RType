/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef NULLRUNTIME_H
#define NULLRUNTIME_H

#include "../IRuntime.hpp"
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
    void loadFont(const std::string& filePath) override {}
    int loadSprite(const std::string& filePath) override { return 0; }
    void drawSprite(const std::string& spriteName, mlg::vec3 position, mlg::vec4 spriteRect,
                    mlg::vec3 scale, float rotation) override
    {
    }
    void drawSprite(const std::string& spriteName, mlg::vec3 position) override {}
    void drawSprite(int IDSprite, mlg::vec3 position, mlg::vec4 spriteRect, mlg::vec3 scale,
                    float rotation) override
    {
    }
    void drawSprite(int IDSprite, mlg::vec3 position) override {}
    void drawText(const std::string& fontPath, const std::string& textStr, const mlg::vec3 position,
                  unsigned int fontSize, const mlg::vec3& color = mlg::vec3(0, 0, 0),
                  bool centered = false) override
    {
    }
    void FullScreenWindow() override {}
    bool isWindowOpen() override { return true; }
    void unloadSprite(int spriteId) override {}
    bool loadMusic(const std::string& filePath) override { return false; }
    void playMusic(const std::string& filePath, bool loop) override {}
    void stopCurrentMusic() override {}
    void unloadMusic(const std::string& musicName) override {}
    int loadSound(const std::string& filePath) override { return false; }
    void playSound(const int soundID) override {}
    void unloadSound(const int soundID) override {}
    void setFramerateLimit(unsigned int limit) override {}
    void setVerticalSyncEnabled(bool enabled) override {}
    void updateSounds() override{};

   private:
    // Member variables
};

}  // namespace RType

#endif  // NULLRUNTIME_H