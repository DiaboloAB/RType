/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "AnimationList.hpp"


Animation AnimationList::getAnimation()
{
    for (auto &anim : animations)
    {
        if (anim.getName() == currentAnim)
        {
            return anim;
        }
    }
    return animations[0];
}

void AnimationList::playAnim(std::string animName)
{
    if (currentAnim == animName)
    {
        return;
    }
    for (auto &anim : animations)
    {
        if (anim.getName() == animName)
        {
            time = 0;
            currentAnim = animName;
            currentFrame = 0;
            return;
        }
    }
}