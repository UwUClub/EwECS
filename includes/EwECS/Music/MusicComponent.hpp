//
// Created by beafowl on 30/10/23.
//

#ifndef R_TYPE_MUSICCOMPONENT_HPP
#define R_TYPE_MUSICCOMPONENT_HPP

#include <string>
#include <SFML/Audio.hpp>

namespace Component {
    enum class MUSIC_STATE {
        PLAYING,
        PLAY,
        PAUSE,
        STOP,
        UNKNOW
    };
    struct MusicComponent
    {
            /**
             * @brief the constructor of Sound
             */
            MusicComponent()
                : _loop(false),
                  _volume(100)
            {}

            /**
             * @brief the constructor of Sound
             * @param path
             * @param loop
             * @param volume
             */
            MusicComponent(const std::string &aPath, float aVolume, bool aLoop)
                : _path(aPath),
                  _loop(aLoop),
                  _volume(aVolume)
            {}

            std::string _path;
            bool _loop;
            float _volume;
            sf::Music *_music;
            MUSIC_STATE _state = MUSIC_STATE::UNKNOW;

    };
} // namespace Component

#endif // R_TYPE_MUSICCOMPONENT_HPP
