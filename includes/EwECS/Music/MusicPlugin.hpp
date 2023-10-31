//
// Created by beafowl on 31/10/23.
//

#ifndef R_TYPE_MUSICPLUGIN_HPP
#define R_TYPE_MUSICPLUGIN_HPP

#include <EwECS/IPlugin.hpp>

namespace ECS {
    class MusicPluginConfig final : public ECS::Plugin::IConfigPlugin
    {
        private:
            MusicPluginConfig();

        public:
            static MusicPluginConfig &getInstance();
            MusicPluginConfig(MusicPluginConfig &&) = default;
            MusicPluginConfig(const MusicPluginConfig &) = default;
            MusicPluginConfig &operator=(MusicPluginConfig &&) = default;
            MusicPluginConfig &operator=(const MusicPluginConfig &) = default;
            ~MusicPluginConfig() final;

            void load(const std::string &aJsonPath) final;

            std::string _configPath;
    };

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
