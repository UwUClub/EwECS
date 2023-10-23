/*
** EPITECH PROJECT, 2023
** EwECS
** File description:
** AssetHandler
*/

#ifndef ASSETHANDLER_HPP_
#define ASSETHANDLER_HPP_
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <type_traits>

template<typename Asset>
concept NonPointer = not std::is_pointer_v<Asset>;
template<typename Asset>
concept Pointer = std::is_pointer_v<Asset>;

namespace ECS::Asset {
    /**
     * @brief
     *
     * @tparam Asset The type of the asset, can be a pointer or not, if it's a pointer, add * at the end of the type
     * @details Add an asset before getting it
     */
    template<typename Asset>
    class AssetHandler
    {
        public:
            //-------------- TYPEDEFS --------------//
            using assetDeleter = std::function<void(Asset &)>;

        private:
            assetDeleter _deleter;
            std::unordered_map<std::string, Asset> _assets;

        public:
            //-------------- CTORS/DTOR --------------//
            /**
             * @brief Construct a new Asset Handler object
             *
             * @param aDeleter The function that will be called when the asset is deleted, by default it will call
             * delete on the asset if it's a pointer
             */
            explicit AssetHandler(assetDeleter aDeleter = customDeleter)
                : _deleter(aDeleter)
            {}

            AssetHandler(AssetHandler &&) noexcept = default;
            AssetHandler(const AssetHandler &) = default;
            AssetHandler &operator=(AssetHandler &&) noexcept = default;
            AssetHandler &operator=(const AssetHandler &) = default;

            /**
             * @brief Destroy the Asset Handler object
             *
             */
            ~AssetHandler()
            {
                for (auto &asset : _assets) {
                    _deleter(asset.second);
                }
            }

            //-------------- METHODS --------------//
            /**
             * @brief Add an asset to the handler
             * @details case where the asset is a pointer
             * @tparam AssetPtr a pointer to the asset
             * @param path the path to the asset
             * @param asset the asset
             */
            template<Pointer AssetPtr>
            void addAsset(const std::string &path, AssetPtr asset)
            {
                if (_assets.find(path) != _assets.end()) {
                    return;
                }
                _assets[path] = asset;
            }

            /**
             * @brief Add an asset to the handler
             * @details case where the asset is not a pointer
             * @tparam AssetRef a reference to the asset
             * @param path the path to the asset
             * @param asset the asset
             */
            template<NonPointer AssetRef>
            void addAsset(const std::string &path, Asset &&asset)
            {
                if (_assets.find(path) != _assets.end()) {
                    return;
                }
                _assets.emplace(path, std::move(asset));
            }

            /**
             * @brief Get the Asset object
             *
             * @param path the path to the asset
             * @return Asset& the asset
             */
            Asset &getAsset(const std::string &path)
            {
                if (_assets.find(path) == _assets.end()) {
                    throw AssetHandlerException("Asset not found");
                }
                return _assets[path];
            }

            /**
             * @brief Remove an asset from the handler
             *
             * @param path the path to the asset
             */
            void removeAsset(const std::string &path)
            {
                if (_assets.find(path) == _assets.end()) {
                    throw AssetHandlerException("Asset not found");
                }
                _deleter(_assets[path]);
                _assets.erase(path);
            }

            /**
             * @brief Clear all the assets from the handler
             *
             */
            void clear()
            {
                for (auto &asset : _assets) {
                    _deleter(asset.second);
                }
                _assets.clear();
            }

        private:
            static void customDeleter(Asset asset)
            {
                if constexpr (std::is_pointer_v<Asset>) {
                    delete asset;
                }
            }

            class AssetHandlerException : public std::exception
            {
                public:
                    explicit AssetHandlerException(const std::string &message)
                        : _message(message)
                    {}

                    const char *what() const noexcept override
                    {
                        return _message.c_str();
                    }

                private:
                    std::string _message;
            };
    };
} // namespace ECS::Asset
#endif /* !ASSETHANDLER_HPP_ */
