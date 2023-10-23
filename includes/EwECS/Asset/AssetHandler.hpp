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
            explicit AssetHandler(assetDeleter aDeleter = customDeleter)
                : _deleter(aDeleter)
            {}

            AssetHandler(AssetHandler &&) noexcept = default;
            AssetHandler(const AssetHandler &) = default;
            AssetHandler &operator=(AssetHandler &&) noexcept = default;
            AssetHandler &operator=(const AssetHandler &) = default;
            ~AssetHandler()
            {
                for (auto &[path, asset] : _assets) {
                    std::cout << "Deleting asset " << path << std::endl;
                    _deleter(asset);
                }
            }

            template<Pointer AssetPtr>
            void addAsset(const std::string &path, AssetPtr asset)
            {
                if (_assets.find(path) != _assets.end()) {
                    return;
                }
                _assets[path] = asset;
            }

            template<NonPointer AssetRef>
            void addAsset(const std::string &path, Asset &&asset)
            {
                if (_assets.find(path) != _assets.end()) {
                    return;
                }
                _assets.emplace(path, std::move(asset));
                std::cout << "Added asset " << path << std::endl;
            }

            Asset &getAsset(const std::string &path)
            {
                if (_assets.find(path) == _assets.end()) {
                    throw AssetHandlerException("Asset not found");
                }
                return _assets[path];
            }

            void removeAsset(const std::string &path)
            {
                if (_assets.find(path) == _assets.end()) {
                    throw AssetHandlerException("Asset not found");
                }
                _deleter(_assets[path]);
                _assets.erase(path);
            }

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
