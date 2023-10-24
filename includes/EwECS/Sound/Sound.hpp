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
            Sound() = default;
            ~Sound() = default;
            Sound(const Sound &aOther) = default;
            Sound(Sound &&aOther) noexcept = default;
            Sound &operator=(const Sound &aOther) = default;
            Sound &operator=(Sound &&aOther) noexcept = default;

            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) override;

            void createSound(const std::string &aPath, bool aLoop, float aVolume);

            static void play(const std::string &aPath, bool aLoop, float aVolume);

            static void stop(const std::string &aPath);

            static void setVolume(const std::string &aPath, float aVolume);

            static void setLoop(const std::string &aPath, bool aLoop);

            static void pause(const std::string &aPath);

            static void resume(const std::string &aPath);

            static void setGlobalVolume(float aVolume);

    };
} // namespace ECS

#endif // EWECS_COMPONENTS_SOUND_HPP
