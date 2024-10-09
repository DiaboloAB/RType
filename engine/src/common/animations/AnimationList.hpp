/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMATIONLIST_HPP
#define ANIMATIONLIST_HPP

#include "Animation.hpp"

/**
 * @class AnimationList
 * @brief Class managing multiple Animations.
 */
class AnimationList
{
   private:
   public:
    std::vector<Animation> animations = {};  ///< Vector of Animations.
    float time = 0;                          ///< Current time.
    std::string currentAnim = "";            ///< Name of the current animation.
    int currentFrame = 0;                    ///< Current frame number.

    /**
     * @brief Constructor for AnimationList.
     */
    AnimationList() {}
    /**
     * @brief Destructor for AnimationList.
     */
    ~AnimationList() {}

    /**
     * @brief Play a specific animation.
     * @param animName The name of the animation to play.
     */
    void playAnim(std::string animName);

    /**
     * @brief Get the current animation.
     * @return The current animation.
     */
    Animation getAnimation();

    /**
     * @brief Add an animation to the list.
     * @param anim The animation to add.
     */
    void addAnimation(Animation anim) { animations.push_back(anim); }

    /**
     * @brief Get the current time.
     * @return The current time.
     */
    float getTime() { return time; }

    /**
     * @brief Get the name of the current animation.
     * @return The name of the current animation.
     */
    std::string getCurrentAnim() { return currentAnim; }

    /**
     * @brief Get the current frame number.
     * @return The current frame number.
     */
    int getCurrentFrame() { return currentFrame; }
};

#endif  // ANIMATIONLIST_HPP