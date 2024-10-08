/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#include "Animation.hpp"

Animation::Animation(const std::string &filepath, int frameCount, float speed,
                     const mlg::vec2 &frameSize, const mlg::vec2 &scale, float rotation,
                     std::string name)
    : filepath(filepath),
      frameCount(frameCount),
      speed(speed),
      frameSize(frameSize),
      scale(scale),
      rotation(rotation),
      name(name)
{
}

Animation::~Animation() {}
