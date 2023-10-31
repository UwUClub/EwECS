//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_COMPONENTS_SOUND_HPP
#define EWECS_COMPONENTS_SOUND_HPP

#include <string>
#include <SFML/Audio.hpp>

namespace Component {
    enum class SOUND_STATE {
        PLAYING,
        PAUSE,
        STOP,
        UNKNOW
    };
    struct SoundComponent
    {
            /**
             * @brief the constructor of Sound
             */
            SoundComponent()
                : _loop(false),
                  _volume(100)
            {}

            /**
             * @brief the constructor of Sound
             * @param path
             * @param loop
             * @param volume
             */
            SoundComponent(const std::string &aPath, float aVolume, bool aLoop)
                : _path(aPath),
                  _loop(aLoop),
                  _volume(aVolume)
            {}

            std::string _path;
            bool _loop;
            float _volume;
            sf::Sound *_sound;
            SOUND_STATE _state = SOUND_STATE::UNKNOW;
    };
} // namespace Component

#endif // EWECS_COMPONENTS_SOUND_HPP
