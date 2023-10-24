//
// Created by beafowl on 24/10/23.
//

#include "Sound.hpp"
#include "Components/Components+Sounds.hpp"
#include "AssetManager.hpp"
#include "World.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

namespace ECS {
    void Sound::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager)
    {
        aWorld.registerComponent<Component::SoundsComponents>();

        aAssetManager.registerAssetHandler<sf::Sound *>();
    }

    void Sound::createSound(const std::string &aPath, bool aLoop, float aVolume)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<>()

        if (sound == nullptr) {
            sound = new sf::Sound();
            Asset::AssetManager::getInstance().addAsset(aPath, sound);
        }
        sound->setLoop(aLoop);
        sound->setVolume(aVolume);
    }

    void Sound::play(const std::string &aPath, bool aLoop, float aVolume)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->setLoop(aLoop);
        sound->setVolume(aVolume);
        sound->play();
    }

    void Sound::stop(const std::string &aPath)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->stop();
    }

    void Sound::setVolume(const std::string &aPath, float aVolume)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->setVolume(aVolume);
    }

    void Sound::setLoop(const std::string &aPath, bool aLoop)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->setLoop(aLoop);
    }

    void Sound::pause(const std::string &aPath)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->pause();
    }

    void Sound::resume(const std::string &aPath)
    {
        auto *sound = Asset::AssetManager::getInstance().getAsset<sf::Sound *>(aPath);

        if (sound == nullptr) {
            return;
        }
        sound->play();
    }

    void Sound::setGlobalVolume(float aVolume)
    {
        sf::Listener::setGlobalVolume(aVolume);
    }
}
