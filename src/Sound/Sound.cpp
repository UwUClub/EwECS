//
// Created by beafowl on 24/10/23.
//

#include "EwECS/Sound/Sound.hpp"
#include <SFML/Audio.hpp>
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Sound/SoundComponent.hpp"
#include "EwECS/World.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/Logger.hpp"

namespace ECS {
    sf::Sound *Sound::initSound(const std::string &aPath)
    {
        auto &assetManager = ECS::Asset::AssetManager::getInstance();
        auto *sound = new sf::Sound();
        std::string const assetPath = Utils::getFilePathInstall();

        if (!assetManager.hasAsset<sf::SoundBuffer *>(assetPath + aPath)) {
            auto *buffer = new sf::SoundBuffer();
            if (!buffer->loadFromFile(assetPath + aPath)) {
                Logger::error("Sound not found: " + assetPath + aPath);
                delete sound;
                delete buffer;
                return nullptr;
            }
            assetManager.addAsset<sf::SoundBuffer *>(assetPath + aPath, buffer);
            sound->setBuffer(*buffer);
        } else {
            sound->setBuffer(*assetManager.getAsset<sf::SoundBuffer *>(assetPath + aPath));
        }
        return sound;
    }

    void Sound::play(Component::SoundComponent &aSound)
    {
        if (aSound._sound == nullptr || aSound._state == Component::SOUND_STATE::UNKNOW) {
            return;
        }
        if (isPlaying(aSound) || aSound._state == Component::SOUND_STATE::PLAYING) {
            return;
        }

        aSound._sound->setLoop(aSound._loop);
        aSound._sound->setVolume(aSound._volume);
        aSound._sound->play();
        aSound._state = Component::SOUND_STATE::PLAYING;
    }

    void Sound::stop(Component::SoundComponent &aSound)
    {
        if (aSound._sound == nullptr) {
            return;
        }
        aSound._sound->stop();
        aSound._state = Component::SOUND_STATE::STOP;
    }

    void Sound::pause(Component::SoundComponent &aSound)
    {
        if (aSound._sound == nullptr) {
            return;
        }
        aSound._sound->pause();
        aSound._state = Component::SOUND_STATE::PAUSE;
    }

    bool Sound::isPlaying(Component::SoundComponent &aSound)
    {
        if (aSound._sound == nullptr) {
            return false;
        }
        return aSound._sound->getStatus() == sf::Sound::Playing;
    }

    void Sound::createSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds)
    {
        ECS::Sound const &sound = ECS::Sound::getInstance();

        for (auto &soundsComponent : aSounds) {
            if (!soundsComponent.has_value() || soundsComponent.value()._sound == nullptr
                || soundsComponent.value()._state != Component::SOUND_STATE::UNKNOW) {
                continue;
            }
            soundsComponent.value()._sound = sound.initSound(soundsComponent.value()._path);
            if (soundsComponent.value()._sound == nullptr) {
                Logger::error("Sound not found: " + soundsComponent.value()._path);
                continue;
            }
            soundsComponent.value()._state = Component::SOUND_STATE::STOP;
        }
    }

    void Sound::playSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds)
    {
        ECS::Sound &sound = ECS::Sound::getInstance();

        for (auto &soundsComponent : aSounds) {
            if (!soundsComponent.has_value() || soundsComponent.value()._state == Component::SOUND_STATE::UNKNOW
                || soundsComponent.value()._sound == nullptr) {
                continue;
            }
            sound.play(soundsComponent.value());
        }
    }

    void Sound::stopSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds)
    {
        ECS::Sound const &sound = ECS::Sound::getInstance();

        for (auto &soundsComponent : aSounds) {
            if (!soundsComponent.has_value() || soundsComponent.value()._state == Component::SOUND_STATE::UNKNOW
                || soundsComponent.value()._sound == nullptr) {
                continue;
            }
            if ((soundsComponent.value()._state == Component::SOUND_STATE::STOP
                 && soundsComponent.value()._sound->getStatus() == sf::Sound::Playing)
                || (soundsComponent.value()._state == Component::SOUND_STATE::PAUSE
                    && soundsComponent.value()._sound->getStatus() == sf::Sound::Paused)) {
                soundsComponent.value()._state = Component::SOUND_STATE::STOP;
                sound.stop(soundsComponent.value());
            }
        }
    }

    void Sound::pauseSound(ECS::Core::SparseArray<Component::SoundComponent> &aSounds)
    {
        ECS::Sound  const &sound = ECS::Sound::getInstance();

        for (auto &soundsComponent : aSounds) {
            if (!soundsComponent.has_value() || soundsComponent.value()._state == Component::SOUND_STATE::UNKNOW
                || soundsComponent.value()._sound == nullptr) {
                continue;
            }
            if (soundsComponent.value()._state == Component::SOUND_STATE::PAUSE
                && soundsComponent.value()._sound->getStatus() == sf::Sound::Playing) {
                sound.pause(soundsComponent.value());
            }
        }
    }
} // namespace ECS
