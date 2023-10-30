//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_SOUND_HPP
    #define EWECS_SOUND_HPP

    #include <string>
    #include "EwECS/IPlugin.hpp"

namespace ECS {
    class Sound : ECS::Plugin::IPlugin
    {
        public:
            /**
             * @brief the constructor of Sound
             */
            Sound() = default;

            /**
             * @brief the destructor of Sound
             */
            ~Sound() override = default;

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
             * @brief plug the plugin
             * @param aWorld
             * @param aAssetManager
             */
            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) override;

            /**
             * @brief create a sound
             * @param aPath
             */
            static void createSound(const std::string &aPath);

            /**
             * @brief play a sound
             * @param aPath
             * @param aLoop
             * @param aVolume
             */
            static void play(const std::string &aPath, bool aLoop, float aVolume);

            /**
             * @brief stop a sound
             * @param aPath
             */
            static void stop(const std::string &aPath);

            /**
             * @brief set the volume of a sound
             * @param aPath
             * @param aVolume
             */
            static void setVolume(const std::string &aPath, float aVolume);

            /**
             * @brief set the loop of a sound
             * @param aPath
             * @param aLoop
             */
            static void setLoop(const std::string &aPath, bool aLoop);

            /**
             * @brief pause a sound
             * @param aPath
             */
            static void pause(const std::string &aPath);

            /**
             * @brief resume a sound
             * @param aPath
            sf::Sound *_sound;
             */
            static void resume(const std::string &aPath);

            /**
             * @brief set the global volume
             * @param aVolume
             */
            static void setGlobalVolume(float aVolume);

            /**
             * @brief see if a sound is playing
             * @param aPath
             * @return true if the sound is playing
             */
            static bool isPlaying(const std::string &aPath);

    };
} // namespace ECS

#endif // EWECS_COMPONENTS_SOUND_HPP
