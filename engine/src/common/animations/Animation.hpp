/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include <string>
#include <mlg/mlg.hpp>
#include <vector>
#include <iostream>

class Animation
{
    private:
        std::string filepath;
        int frameCount;
        float speed;
        mlg::vec2 frameSize;
        mlg::vec2 scale;
        float rotation;
        std::string name;
    public:
        Animation(const std::string &filepath, int frameCount, float speed, const mlg::vec2 &frameSize, const mlg::vec2 &scale, float rotation, std::string name);
        ~Animation();

        mlg::vec4 getSpriteCoords(int frame)
        {
            return mlg::vec4(
                frame * frameSize.x,
                0,
                frameSize.x,
                frameSize.y
            );
        }

        std::string getFilePath() { return filepath; }
        int getFrameCount() { return frameCount; }
        float getFrameDuration() { return speed; }
        mlg::vec2 getFrameSize() { return frameSize; }
        mlg::vec2 getScale() { return scale; }
        float getRotation() { return rotation; }
        std::string getName() { return name; }
};

class Animations
{
    private:

    public:
        std::vector<Animation> animations = {};
        float time = 0;
        std::string currentAnim = "";
        int currentFrame = 0;
        
        Animations() {}
        ~Animations() {}

        void playAnim(std::string animName)
        {
            if (currentAnim == animName)
            {
                return;
            }
            for (auto& anim : animations)
            {
                if (anim.getName() == animName)
                {
                    time = 0;
                    currentAnim = animName;
                    std::cout << "playing anim: " << animName << std::endl;
                    return;
                }
            }
        }

        Animation getAnimation()
        {
            for (auto& anim : animations)
            {
                if (anim.getName() == currentAnim)
                {
                    return anim;
                }
            }
            return animations[0];
        }

        void addAnimation(Animation anim)
        {
            animations.push_back(anim);
        }

        float getTime() { return time; }
        std::string getCurrentAnim() { return currentAnim; }
        int getCurrentFrame() { return currentFrame; }
};