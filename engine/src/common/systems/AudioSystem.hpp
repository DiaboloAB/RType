/**********************************************************************************
 * Project: RType
 * Description: A GAME ENGINE THAT ROARS !
 * Author: Alexis BOITEL, Raphael MABILLE, Morgan LARGEOT, Maxence LARGEOT, Arthur DORIEL
 * Date, Location: 2024, Rennes
 **********************************************************************************/

#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <system/ISystem.hpp>
// std

namespace RType {

class AudioSystem : public ISystem {
public:
    AudioSystem() {}
    ~AudioSystem() {}

    void load(mobs::Registry& registry, GameContext& gameContext) override
    {
        auto view = registry.view<Audio>();
        for (auto entity : view)
        {
            auto& audio = view.get<Audio>(entity);
            for (const auto& sound : audio.sounds)
            {
                gameContext._runtime->loadSound(sound);
            }
            for (const auto& music : audio.musics)
            {
                gameContext._runtime->loadMusic(music);
            }
        }
    }

    void update(mobs::Registry& registry, GameContext& gameContext) override
    {
        auto view = registry.view<Audio>();
        for (auto entity : view)
        {   
            auto& audio = view.get<Audio>(entity);
            if (audio.audioQueue.size() > 0)
            {
                auto sound = audio.audioQueue.front();
                audio.audioQueue.pop();
                if (std::find(audio.musics.begin(), audio.musics.end(), sound) != audio.musics.end())
                {
                    gameContext._runtime->playMusic(sound, true);
                }
                else if (std::find(audio.sounds.begin(), audio.sounds.end(), sound) != audio.sounds.end())
                {
                    gameContext._runtime->playSound(sound);
                }
            }
        }
    }

    // Getters

    // Setters

private:
    // Member variables
};

}  // namespace RType

#endif // AUDIOSYSTEM_H