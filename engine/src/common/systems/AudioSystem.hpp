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

namespace RType
{

class AudioSystem : public ISystem
{
   public:
    AudioSystem() {}
    ~AudioSystem() {}

    void load(mobs::Registry& registry, GameContext& gameContext) override
    {
        auto view = registry.view<Audio>();
        for (auto entity : view)
        {
            std::cout << "Loading audio for entity " << entity << std::endl;
            auto& audio = view.get<Audio>(entity);
            for (auto sound : audio.soundList)
            {
                audio.soundList[sound.first] =
                    gameContext._runtime->loadSound(gameContext._assetsPath + sound.first);
            }
            for (auto music : audio.musicList)
            {
                audio.musicList[music.first] =
                    gameContext._runtime->loadMusic(gameContext._assetsPath + music.first);
            }
        }
    }

    void update(mobs::Registry& registry, GameContext& gameContext) override
    {
        auto view = registry.view<Audio>();
        for (auto entity : view)
        {
            auto& audio = view.get<Audio>(entity);
            if (!audio.audioQueue.empty())
            {
                auto sound = audio.audioQueue.front();
                audio.audioQueue.pop();
                if (audio.soundList.find(sound) != audio.soundList.end())
                {
                    gameContext._runtime->playSound(audio.soundList[sound]);
                }
                else if (audio.musicList.find(sound) != audio.musicList.end())
                {
                    gameContext._runtime->playMusic(audio.musicList[sound]);
                }
            }
        }
    }

   private:
    // Member variables
};

}  // namespace RType

#endif  // AUDIOSYSTEM_H