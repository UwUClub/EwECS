//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_SOUND_HPP
    #define EWECS_SOUND_HPP

    #include <string>
    #include <SFML/Audio.hpp>
    #include <vector>
    #include <unordered_map>
    #include <memory>
    #include "EwECS/Sound/SoundComponent.hpp"
    #include "EwECS/SparseArray.hpp"

namespace ECS {
    class Sound
    {
        public:
            /**
             * @brief get the instance of Sound
             * @return Sound
             */
            static Sound &getInstance()
            {
                static Sound instance;
                return instance;
            }

            /**
             * @brief the constructor of Sound
             */
            Sound() = default;

            /**
             * @brief the copy constructor of Sound
             */
            Sound(const Sound &aOther) = default;

            /**
             * @brief the move constructor of Sound
             */
            Sound(Sound &&aOther) noexcept = default;

            /**
             * @brief the copy assignment of Sound
             */
            Sound &operator=(const Sound &aOther) = default;

            /**
             * @brief the move assignment of Sound
             */
            Sound &operator=(Sound &&aOther) noexcept = default;

            /**
             * @brief create a sound
             *
             * @param aPath
             */
            static sf::Sound *initSound(const std::string &aPath);

            /**
             * @brief play a sound
             *
             * @param aPath
             * @param aLoop
             * @param aVolume
             */
            void play(Component::SoundComponent &aSound);

            /**
             * @brief stop a sound
             *
             * @param aPath
             */
            static void stop(Component::SoundComponent &aSound);

            /**
             * @brief pause a sound
             *
             * @param aPath
             */
            static void pause(Component::SoundComponent &aSound);

            /**
             * @brief see if a sound is playing
             *
             * @param aPath
             * @return true if the sound is playing
             */
            static bool isPlaying(Component::SoundComponent &aSound);

            /**
             * @brief create a sound
             *
             * @param aSounds
             */
            static void createSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds);

            /**
             * @brief play a sound
             *
             * @param aSounds
             */
            static void playSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds);

            /**
             * @brief stop a sound
             *
             * @param aSounds
             */
            static void stopSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds);

            /**
             * @brief pause a sound
             *
             * @param aSounds
             */
            static void pauseSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds);
    };
} // namespace ECS

#endif // EWECS_COMPONENTS_SOUND_HPP
