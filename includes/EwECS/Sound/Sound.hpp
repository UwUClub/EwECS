//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_COMPONENTS_SOUND_HPP
    #define EWECS_SOUND_HPP

    #include <string>
    #include "IPlugin.hpp"

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
            void createSound(const std::string &aPath);

            /**
             * @brief play a sound
             * @param aPath
             * @param aLoop
             * @param aVolume
             */
            void play(const std::string &aPath, bool aLoop, float aVolume);

            /**
             * @brief stop a sound
             * @param aPath
             */
            void stop(const std::string &aPath);

            /**
             * @brief set the volume of a sound
             * @param aPath
             * @param aVolume
             */
            void setVolume(const std::string &aPath, float aVolume);

            /**
             * @brief set the loop of a sound
             * @param aPath
             * @param aLoop
             */
            void setLoop(const std::string &aPath, bool aLoop);

            /**
             * @brief pause a sound
             * @param aPath
             */
            void pause(const std::string &aPath);

            /**
             * @brief resume a sound
             * @param aPath
             */
            void resume(const std::string &aPath);

            /**
             * @brief set the global volume
             * @param aVolume
             */
            void setGlobalVolume(float aVolume);

    };
} // namespace ECS

#endif // EWECS_COMPONENTS_SOUND_HPP
