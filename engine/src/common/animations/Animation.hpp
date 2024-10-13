/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <iostream>
#include <mlg/mlg.hpp>
#include <string>
#include <vector>

/**
 * @class Animation
 * @brief Class representing an animation.
 */
class Animation
{
   private:
    std::string filepath;  ///< Path to the file containing the animation.
    int frameCount;        ///< Number of frames in the animation.
    float speed;           ///< Speed of the animation.
    mlg::vec3 frameSize;   ///< Size of each frame.
    mlg::vec3 scale;       ///< Scale of the animation.
    float rotation;        ///< Rotation of the animation.
    std::string name;      ///< Name of the animation.
    bool loop;             ///< Boolean to know if the animation should loop.

   public:
    /**
     * @brief Constructor for Animation.
     * @param filepath Path to the file containing the animation.
     * @param frameCount Number of frames in the animation.
     * @param speed Speed of the animation.
     * @param frameSize Size of each frame.
     * @param scale Scale of the animation.
     * @param rotation Rotation of the animation.
     * @param name Name of the animation.
     * @param loop Boolean to know if the animation should loop.
     */
    Animation(const std::string &filepath, int frameCount, float speed, const mlg::vec3 &frameSize,
              const mlg::vec3 &scale, float rotation, std::string name, bool loop);
    /**
     * @brief Destructor for Animation.
     */
    ~Animation();

    /**
     * @brief Get the sprite coordinates for a given frame.
     * @param frame The frame number.
     * @return The sprite coordinates as mlg::vec4.
     */
    mlg::vec4 getSpriteCoords(int frame);

    /**
     * @brief Get the file path of the animation.
     * @return The file path as a string.
     */
    std::string getFilePath() { return filepath; }

    /**
     * @brief Get the number of frames in the animation.
     * @return The number of frames.
     */
    int getFrameCount() { return frameCount; }

    /**
     * @brief Get the Speed of each frame.
     * @return The frame speed.
     */
    float getFrameSpeed() { return speed; }

    /**
     * @brief Get the size of each frame.
     * @return The frame size as mlg::vec2.
     */
    mlg::vec3 getFrameSize() { return frameSize; }

    /**
     * @brief Get the scale of the animation.
     * @return The scale as mlg::vec2.
     */
    mlg::vec3 getScale() { return scale; }

    /**
     * @brief Get the rotation of the animation.
     * @return The rotation.
     */
    float getRotation() { return rotation; }

    /**
     * @brief Get the name of the animation.
     * @return The name as a string.
     */
    std::string getName() { return name; }

    /**
     * @brief Check if the animation should loop.
     * @return True if the animation should loop, false otherwise.
     */
    bool getLoop() { return loop; }
};

#endif  // ANIMATION_HPP