//
// Created by beafowl on 31/10/23.
//

#ifndef R_TYPE_SOUNDPLUGIN_HPP
#define R_TYPE_SOUNDPLUGIN_HPP

#include <EwECS/IPlugin.hpp>

namespace ECS {
    class SoundPlugin final : public ECS::Plugin::IPlugin
    {
        public:
            SoundPlugin();
            SoundPlugin(SoundPlugin &&) = delete;
            SoundPlugin(const SoundPlugin &) = delete;
            SoundPlugin &operator=(SoundPlugin &&) = delete;
            SoundPlugin &operator=(const SoundPlugin &) = delete;
            ~SoundPlugin() final;

            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) final;
    };
} // namespace ECS::Sound

#endif // R_TYPE_SOUNDPLUGIN_HPP
