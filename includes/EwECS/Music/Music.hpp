//
// Created by beafowl on 30/10/23.
//

#ifndef R_TYPE_MUSIC_HPP
#define R_TYPE_MUSIC_HPP

    #include <string>
    #include <SFML/Audio.hpp>
    #include <vector>
    #include <unordered_map>
    #include <memory>
    #include "EwECS/IPlugin.hpp"
    #include "EwECS/Music/MusicComponent.hpp"
    #include "EwECS/SparseArray.hpp"

namespace ECS {
    class Music
    {
        public:
            /**
             * @brief get the instance of Sound
             *
             * @return Music
             */
            static Music &getInstance()
            {
                static Music instance;
                return instance;
            }

            /**
             * @brief the constructor of Sound
             */
            Music() = default;

            /**
             * @brief the copy constructor of Sound
             */
            Music(const Music &aOther) = default;

            /**
             * @brief the move constructor of Sound
             */
            Music(Music &&aOther) noexcept = default;

            /**
             * @brief the copy assignment of Sound
             */
            Music &operator=(const Music &aOther) = default;

            /**
             * @brief the move assignment of Sound
             */
            Music &operator=(Music &&aOther) noexcept = default;

            /**
             * @brief create a sound
             *
             * @param aPath
             */
            static sf::Music *initMusic(const std::string &aPath);

            /**
             * @brief play a sound
             *
             * @param aPath
             * @param aLoop
             * @param aVolume
             */
            static void play(Component::MusicComponent &aMusicComponent);

            /**
             * @brief stop a sound
             *
             * @param aPath
             */
            static void stop(Component::MusicComponent &aMusicComponent);

            /**
             * @brief pause a sound
             *
             * @param aPath
             */
            static void pause(Component::MusicComponent &aMusicComponent);

            /**
             * @brief check if a sound is playing
             *
             * @param aPath
             * @return
             */
            static bool isPlaying(Component::MusicComponent &aMusicComponent);

            /**
             * @brief Add music to the game
             *
             * @param aMusic SparseArray of all entities music
             */
            static void createMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic);

            /**
             * @brief Play music to the game
             *
             * @param aMusic SparseArray of all entities music
             */
            static void playMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic);

            /**
             * @brief Stop music to the game
             *
             * @param aMusic SparseArray of all entities music
             */
            static void stopMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic);

            /**
             * @brief Pause music to the game
             *
             * @param aMusic SparseArray of all entities music
             */
            static void pauseMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic);
    };
}

#endif // R_TYPE_MUSIC_HPP
