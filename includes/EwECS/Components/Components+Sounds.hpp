//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_COMPONENTS_SOUND_HPP
#define EWECS_COMPONENTS_SOUND_HPP

#include <string>

namespace Component {
    struct SoundsComponents
    {
            /**
             * @brief the constructor of Sound
             */
            SoundsComponents()
                : _loop(false),
                  _volume(100)
            {}

            /**
             * @brief the constructor of Sound
             * @param path
             * @param loop
             * @param volume
             */
            SoundsComponents(const std::string &aPath, bool aLoop, float aVolume)
                : _path(aPath),
                  _loop(aLoop),
                  _volume(aVolume)
            {}

            std::string _path;
            [[maybe_unused]] bool _loop;
            [[maybe_unused]] float _volume;
    };
} // namespace Component

#endif // EWECS_COMPONENTS_SOUND_HPP
