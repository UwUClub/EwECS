/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** IPlugin
*/

#ifndef IPLUGIN_HPP_
#define IPLUGIN_HPP_

#include <string>
namespace ECS::Core {
    class World;
}

namespace ECS::Asset {
    class AssetManager;
}

namespace ECS::Plugin {
    class IPlugin
    {
        public:
            virtual ~IPlugin() = default;

            virtual void plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager) = 0;
    };

    class IConfigPlugin
    {
        public:
            virtual ~IConfigPlugin() = default;

            virtual void load(const std::string &aJsonPath) = 0;
    };
} // namespace ECS::Plugin
#endif /* !IPLUGIN_HPP_ */
