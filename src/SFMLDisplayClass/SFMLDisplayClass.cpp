/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <functional>
#include <iostream>
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Event/EventManager.hpp"
#include "EwECS/Event/KeyboardEvent.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"

#if defined(__linux__)
    #include <libgen.h>
    #include <limits.h>
    #include <unistd.h>
#endif

namespace ECS {
    SFMLDisplayClass::SFMLDisplayClass()
    {
        auto &renderConfig = Render::RenderPluginConfig::getInstance();

        _window.create(sf::VideoMode(renderConfig._windowWidth, renderConfig._windowHeight), renderConfig._windowName);
        /*if (_window == nullptr) {
            std::cout << "Failed to create SFML window: " << std::endl;
            return;
        }*/
#if defined(__linux__)
        char result[PATH_MAX];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        if (count < 0 || count >= PATH_MAX) {
            _assetPath = "./";
            return;
        }
        result[count] = '\0';
        char *dir = dirname(result);
        if (dir == nullptr) {
            _assetPath = "./";
            return;
        }
        _assetPath = std::string(dir) + "/";
#else
        _assetPath = "./";
#endif
    }

    sf::Texture *SFMLDisplayClass::getTexture(const std::string &aPath)
    {
        std::string path = _assetPath + aPath;
        auto *texture = new sf::Texture();
        auto &assetManager = ECS::Asset::AssetManager::getInstance();

        if (!assetManager.hasAsset<sf::Texture *>(path)) {
            if (texture->loadFromFile(path.c_str())) {
                assetManager.addAsset<sf::Texture *>(path, texture);
                return assetManager.getAsset<sf::Texture *>(path);
            }
            std::cerr << "Failed to create texture" << std::endl;
            assetManager.removeAsset<sf::Texture *>(path);
            return nullptr;
        }
        return assetManager.getAsset<sf::Texture *>(path);
    }

    void SFMLDisplayClass::getInput()
    {
        Event::EventManager *eventManager = Event::EventManager::getInstance();
        SFMLDisplayClass *display = &SFMLDisplayClass::getInstance();
        sf::Event event;

        while (display->_window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && (_keyMap.find(event.key.code) != _keyMap.end())) {
                try {
                    eventManager->pushEvent<Event::KeyboardEvent>(
                        Event::KeyboardEvent(_keyMap.at(event.key.code), Event::KeyState::PRESSED));
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            if (event.type == sf::Event::Closed) {
                display->_window.close();
                Core::World::getInstance().stop();
            }
        }
    }

    void SFMLDisplayClass::displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                           Core::SparseArray<Utils::Vector2f> &aPos)
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        auto &world = Core::World::getInstance();
        const auto size = aSprites.size();

        display._window.clear(sf::Color::Black);
        for (size_t i = 0; i < size; i++) {
            if (!aSprites[i].has_value() || aSprites[i]->texture == nullptr) {
                continue;
            }
            if (!aPos[i].has_value()) {
                continue;
            }

            auto &spriteData = aSprites[i].value();
            auto &pos = aPos[i].value();

            if (!spriteData.rect.empty()) {
                sf::Sprite sprite;

                spriteData.timer += world.getDeltaTime();
                if (spriteData.timer >= spriteData.rectTime[spriteData.currentRect]) {
                    spriteData.timer = 0;
                    spriteData.currentRect++;
                    if (spriteData.currentRect >= spriteData.rect.size()) {
                        spriteData.currentRect = 0;
                    }
                }
                sprite.setTexture(*spriteData.texture);
                sprite.setTextureRect(spriteData.rect[spriteData.currentRect]);
                sprite.setPosition(pos.x, pos.y);
                sprite.scale(spriteData.scale, spriteData.scale);
                display._window.draw(sprite);
            }
        }
    }

    void SFMLDisplayClass::loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites)
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();

        for (auto &aSprite : aSprites) {
            if (!aSprite.has_value() || aSprite.value().texture != nullptr) {
                continue;
            }
            aSprite.value().texture = display.getTexture(aSprite.value().path);
            if (aSprite.value().texture == nullptr) {
                std::cerr << "Failed to load texture: " << aSprite.value().path << std::endl;
            }
        }
    }

    void SFMLDisplayClass::displayTexts(Core::SparseArray<Component::TextComponent> &aTexts)
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();
        Render::RenderPluginConfig &renderConfig = Render::RenderPluginConfig::getInstance();

        if (!renderConfig._isFontLoaded) {
            return;
        }
        for (auto &aText : aTexts) {
            if (!aText.has_value()) {
                continue;
            }
            auto &text = aText.value().text;

            if (text.getFont() == nullptr) {
                text.setFont(renderConfig._font);
            }
            display._window.draw(text);
        }
    }

    void SFMLDisplayClass::display()
    {
        SFMLDisplayClass &display = SFMLDisplayClass::getInstance();

        display._window.display();
    }

    SFMLDisplayClass::~SFMLDisplayClass()
    {
        _window.close();
    }
} // namespace ECS
