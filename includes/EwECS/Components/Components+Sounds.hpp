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
                : loop(false),
                  volume(100)
            {}

            /**
             * @brief the constructor of Sound
             * @param path
             * @param loop
             * @param volume
             */
            SoundsComponents(const std::string &path, bool loop, float volume)
                : path(path),
                  loop(loop),
                  volume(volume)
            {}

            std::string path;
            bool loop;
            float volume;
    };
} // namespace Component

#endif // EWECS_COMPONENTS_SOUND_HPP
