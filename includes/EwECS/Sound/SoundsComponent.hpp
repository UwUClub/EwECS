//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_COMPONENTS_SOUND_HPP
#define EWECS_COMPONENTS_SOUND_HPP

#include <string>
#include <SFML/Audio.hpp>

namespace Component {
    struct SoundsComponents
    {
            /**
             * @brief the constructor of Sound
             */
            SoundsComponents()
                : _loop(false),
                  _volume(100),
                  _isPlayed(false)
            {}

            /**
             * @brief the constructor of Sound
             * @param path
             * @param loop
             * @param volume
             */
            SoundsComponents(const std::string &aPath, bool aLoop, float aVolume, bool aIsPlayed)
                : _path(aPath),
                  _loop(aLoop),
                  _volume(aVolume),
                  _isPlayed(aIsPlayed)
            {}

            std::string _path;
            bool _loop;
            float _volume;
            bool _isPlayed;
    };
} // namespace Component

#endif // EWECS_COMPONENTS_SOUND_HPP
