/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** RenderPlugin
*/

#ifndef RENDERPLUGIN_HPP_
#define RENDERPLUGIN_HPP_

#include "EwECS/IPlugin.hpp"

namespace ECS::Render {
    static const std::string RENDER_PLUGIN_CONFIG_BASE = "RenderPlugin";

    class RenderPluginConfig final : public ECS::Plugin::IConfigPlugin
    {
        private:
            RenderPluginConfig();

        public:
            static RenderPluginConfig &getInstance();
            RenderPluginConfig(RenderPluginConfig &&) = default;
            RenderPluginConfig(const RenderPluginConfig &) = default;
            RenderPluginConfig &operator=(RenderPluginConfig &&) = default;
            RenderPluginConfig &operator=(const RenderPluginConfig &) = default;
            ~RenderPluginConfig() final;

            void load(const std::string &aJsonPath) final;

            std::string _windowName;
            std::size_t _windowWidth;
            std::size_t _windowHeight;
            std::string _configPath;
    };

    class RenderPlugin final : public ECS::Plugin::IPlugin
    {
        public:
            RenderPlugin();
            RenderPlugin(RenderPlugin &&) = delete;
            RenderPlugin(const RenderPlugin &) = delete;
            RenderPlugin &operator=(RenderPlugin &&) = delete;
            RenderPlugin &operator=(const RenderPlugin &) = delete;
            ~RenderPlugin() final;

            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) final;

        private:
    };
} // namespace ECS::Render

#endif /* !RENDERPLUGIN_HPP_ */
