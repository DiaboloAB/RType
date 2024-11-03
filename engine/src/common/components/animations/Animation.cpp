/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "Animation.hpp"

Animation::Animation(const std::string &filepath, int frameCount, float speed,
                     const mlg::vec3 &frameSize, std::string name, bool loop)
    : filepath(filepath),
      frameCount(frameCount),
      speed(speed),
      frameSize(frameSize),
      name(name),
      loop(loop)
{
}

Animation::~Animation() {}

mlg::vec4 Animation::getSpriteCoords(int frame)
{
    return mlg::vec4(frame * frameSize.x, 0, frameSize.x, frameSize.y);
}
