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
            //-------------- CTORS/DTOR --------------//
            /**
             * @brief Get the Instance object
             *
             * @return AssetManager&
             */
            static AssetManager &getInstance() noexcept;

            AssetManager(AssetManager &&) = default;
            AssetManager(const AssetManager &) = default;
            AssetManager &operator=(AssetManager &&) = default;
            AssetManager &operator=(const AssetManager &) = default;
            ~AssetManager() = default;

            //-------------- METHODS --------------//
            /**
             * @brief Get the Asset Handler object
             *
             * @tparam Asset The type of the asset, can be a pointer or not, if it's a pointer, add * at the end of the
             * type
             * @return AssetHandler<Asset>& The asset handler
             */
            template<typename Asset>
            AssetHandler<Asset> &getAssetHandler()
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) == _assetsHandlers.end()) {
                    _assetsHandlers[typeIndex] = AssetHandler<Asset>();
                }
                return std::any_cast<AssetHandler<Asset> &>(_assetsHandlers[typeIndex]);
            }

            /**
             * @brief Register a type of asset to handle
             * @details case of a pointer
             * @tparam Asset The type of the asset, is a pointer or not, if it's a pointer, add * at the end of the
             * @param aDeleter The function that will be called when the asset is deleted, by default it will call
             * delete on the asset if it's a pointer
             * @return AssetHandler<Asset>& The asset handler
             */
            template<Pointer Asset>
            AssetHandler<Asset> &RegisterAssetHandler(std::function<void(Asset)> aDeleter)
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) != _assetsHandlers.end()) {
                    throw AssetManagerException("Asset type already registered");
                }
                _assetsHandlers[typeIndex] = AssetHandler<Asset>(aDeleter);
                return std::any_cast<AssetHandler<Asset> &>(_assetsHandlers[typeIndex]);
            }

            /**
             * @brief Register a type of asset to handle
             * @details case of a non pointer
             * @tparam Asset The type of the asset, not a ptr
             * @param aDeleter The function that will be called when the asset is deleted, by default it will do nothing
             * @return AssetHandler<Asset>& The asset handler
             */
            template<NonPointer Asset>
            AssetHandler<Asset> &RegisterAssetHandler(std::function<void(const Asset &)> aDeleter)
            {
                auto typeIndex = std::type_index(typeid(Asset));

                if (_assetsHandlers.find(typeIndex) != _assetsHandlers.end()) {
                    throw AssetManagerException("Asset type already registered");
                }
                _assetsHandlers[typeIndex] = AssetHandler<Asset>(aDeleter);
                return std::any_cast<AssetHandler<Asset> &>(_assetsHandlers[typeIndex]);
            }

            /**
             * @brief Add an asset to the handler
             * @details case where the asset is a pointer, if the asset has not been registered yet, it will be but with
             * the default deleter
             * @tparam Asset a pointer to the asset
             * @param path the path to the asset
             * @param asset the asset
             */
            template<Pointer Asset>
            void addAsset(const std::string &path, Asset asset)
            {
                if (asset == nullptr) {
                    throw AssetManagerException("Asset is nullptr");
                }
                try {
                    getAssetHandler<Asset>().addAsset(path, asset);
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            /**
             * @brief Add an asset to the handler
             * @details case where the asset is not a pointer, if the asset has not been registered yet, it will be but
             * with the default deleter (does nothing on non pointer)
             * @tparam Asset a reference to the asset
             * @param path the path to the asset
             * @param asset the asset
             */
            template<NonPointer Asset>
            void addAsset(const std::string &path, Asset &&asset)
            {
                try {
                    getAssetHandler<Asset>().template addAsset<Asset>(path, std::forward<Asset>(asset));
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            /**
             * @brief Remove an asset from the handler
             *
             * @tparam Asset The type of the asset, can be a pointer or not, if it's a pointer, add * at the end of the
             * type
             * @param path the path to the asset
             */
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

            /**
             * @brief Get the Asset object
             *
             * @tparam Asset The type of the asset, can be a pointer or not, if it's a pointer, add * at the end of the
             * type
             * @param path the path to the asset
             * @return Asset& the asset
             */
            template<typename Asset>
            Asset &getAsset(const std::string &path)
            {
                try {
                    return getAssetHandler<Asset>().getAsset(path);
                } catch (const std::exception &e) {
                    throw AssetManagerException(e.what());
                }
            }

            /**
             * @brief Clear all the assets of a type
             *
             * @tparam Asset The type of the asset, can be a pointer or not, if it's a pointer, add * at the end of the
             * type
             */
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
