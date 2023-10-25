/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** RenderPlugin
*/

#ifndef PHYSICPLUGIN_HPP_
#define PHYSICPLUGIN_HPP_

#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/IPlugin.hpp"
#include "EwECS/Physic/HitBox.hpp"
#include "EwECS/Physic/Weight.hpp"
#include "EwECS/SparseArray.hpp"
#include "EwECS/Utils.hpp"

namespace ECS::Physic {
    static const std::string PHYSIC_PLUGIN_CONFIG_BASE = "config/Gravity.json";

    class PhysicPluginConfig final : public ECS::Plugin::IConfigPlugin
    {
        public:
            static PhysicPluginConfig &getInstance();

            PhysicPluginConfig();
            PhysicPluginConfig(PhysicPluginConfig &&) = default;
            PhysicPluginConfig(const PhysicPluginConfig &) = default;
            PhysicPluginConfig &operator=(PhysicPluginConfig &&) = default;
            PhysicPluginConfig &operator=(const PhysicPluginConfig &) = default;
            ~PhysicPluginConfig() final;

            void load(const std::string &aJsonPath) final;

            float _gravity;
            float _initialJumpVelocity;
            std::string _configPath;
    };

    class PhysicPlugin final : public ECS::Plugin::IPlugin
    {
        public:
            PhysicPlugin();
            PhysicPlugin(PhysicPlugin &&) = delete;
            PhysicPlugin(const PhysicPlugin &) = delete;
            PhysicPlugin &operator=(PhysicPlugin &&) = delete;
            PhysicPlugin &operator=(const PhysicPlugin &) = delete;
            ~PhysicPlugin() final;

            void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) final;

        private:
            static void checkCollision(Core::SparseArray<Utils::Vector2f> &aPos,
                                       Core::SparseArray<Component::HitBox> &aHitBox);
            static void applyGravity(Core::SparseArray<Utils::Vector2f> &aPos,
                                     Core::SparseArray<Component::Weight> &aWeight);
    };
} // namespace ECS::Physic

#endif /* !PHYSICPLUGIN_HPP_ */
