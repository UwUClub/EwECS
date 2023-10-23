/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** AssetManager
*/

#ifndef ASSETMANAGER_HPP_
#define ASSETMANAGER_HPP_

#include <any>
#include <functional>
#include <string>
#include <typeindex>
#include "AssetHandler.hpp"
#include <unordered_map>

namespace ECS::Asset {
    class AssetManager
    {
        private:
            std::unordered_map<std::type_index, std::any> _assetsHandlers;
            AssetManager() = default;

        public:
            static AssetManager &getInstance()
            {
                static AssetManager instance;
                return instance;
            }

            AssetManager(AssetManager &&) = default;
            AssetManager(const AssetManager &) = default;
            AssetManager &operator=(AssetManager &&) = default;
            AssetManager &operator=(const AssetManager &) = default;
            ~AssetManager() = default;

            template<typename Asset>
            AssetHandler<Asset> &getAssetHandler()
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) == _assetsHandlers.end()) {
                    _assetsHandlers[typeIndex] = AssetHandler<Asset>();
                }
                return std::any_cast<AssetHandler<Asset> &>(_assetsHandlers[typeIndex]);
            }

            template<typename Asset>
            AssetHandler<Asset> &RegisterAssetHandler(std::function<void(Asset)> aDeleter)
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) != _assetsHandlers.end()) {
                    throw AssetManagerException("Asset type already registered");
                }
                _assetsHandlers[typeIndex] = AssetHandler<Asset>(aDeleter);
                return std::any_cast<AssetHandler<Asset> &>(_assetsHandlers[typeIndex]);
            }

            template<typename Asset>
            void addAsset(const std::string &path, Asset asset)
            {
                try {
                    getAssetHandler<Asset>().addAsset(path, asset);
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            template<typename Asset>
            void removeAsset(const std::string &path)
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) == _assetsHandlers.end()) {
                    throw AssetManagerException("Asset type not found");
                }

                try {
                    getAssetHandler<Asset>().removeAsset(path);
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            template<typename Asset>
            Asset &getAsset(const std::string &path)
            {
                try {
                    return getAssetHandler<Asset>().getAsset(path);
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            template<typename Asset>
            void clearAssets()
            {
                try {
                    getAssetHandler<Asset>().clear();
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

        private:
            class AssetManagerException : public std::exception
            {
                private:
                    std::string _message;

                public:
                    explicit AssetManagerException(const std::string &message)
                        : _message(message)
                    {}

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }
            };
    };
} // namespace ECS::Asset

#endif /* !ASSETMANAGER_HPP_ */
