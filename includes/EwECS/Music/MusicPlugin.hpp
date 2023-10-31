//
// Created by beafowl on 31/10/23.
//

#ifndef R_TYPE_MUSICPLUGIN_HPP
#define R_TYPE_MUSICPLUGIN_HPP

#include <EwECS/IPlugin.hpp>

namespace ECS {
    class MusicPlugin final : public ECS::Plugin::IPlugin
    {
        public:
            MusicPlugin();
            MusicPlugin(MusicPlugin &&) = delete;
            MusicPlugin(const MusicPlugin &) = delete;
            MusicPlugin &operator=(MusicPlugin &&) = delete;
            MusicPlugin &operator=(const MusicPlugin &) = delete;
            ~MusicPlugin() final;

            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) final;
    };
} // namespace ECS::Sound

#endif // R_TYPE_MUSICPLUGIN_HPP
