/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#include "SFMLDisplayClass.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>
#include "EventManager.hpp"
#include "KeyboardEvent.hpp"
#include <algorithm>
#include <iostream>
#include "World.hpp"
#include "LoadedSprite.hpp"
#include "Utils.hpp"
#include "ConfigReader.hpp"
#if defined(__linux__)
    #include <libgen.h>
    #include <limits.h>
    #include <unistd.h>
#endif

namespace ECS {
    SFMLDisplayClass::SFMLDisplayClass()
    {
        auto &configReader = ConfigReader::getInstance();
        configReader.loadConfig();
        auto &graphicsConf = configReader.get()["graphics"];
        
        _window.create(sf::VideoMode(graphicsConf["width"], graphicsConf["height"]), "R-Type");
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

        if (_textures.find(path) == _textures.end()) {
            if (texture->loadFromFile(path.c_str())) {
                _textures[path] = texture;
            }
            if (_textures[path] == nullptr) {
                std::cerr << "Failed to create texture" << std::endl;
                delete texture;
                return nullptr;
            }
        }
        return _textures[path];
    }

    void SFMLDisplayClass::freeRects(const std::size_t &aIdx)
    {
        auto &world = ECS::Core::World::getInstance();
        auto &sprites = world.getComponent<Component::LoadedSprite>();

        if (!sprites[aIdx].has_value()) {
            return;
        }
        delete sprites[aIdx]->rect;
        delete sprites[aIdx]->srcRect;
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

            if (spriteData.srcRect != nullptr) {
                sf::Sprite sprite;

                sprite.setTexture(*spriteData.texture);
                sprite.setTextureRect(*spriteData.rect);
                sprite.setPosition(pos.x, pos.y);
                sprite.scale(spriteData.scale, spriteData.scale);
                display._window.draw(sprite);
            }
        }
        display._window.display();
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

    SFMLDisplayClass::~SFMLDisplayClass()
    {
        auto &world = ECS::Core::World::getInstance();
        auto &sprites = world.getComponent<Component::LoadedSprite>();

        for (auto &sprite : sprites) {
            if (!sprite.has_value()) {
                continue;
            }
            delete sprite->rect;
            delete sprite->srcRect;
        }
        for (auto &texture : _textures) {
            delete texture.second;
        }
        _window.close();
    }
}