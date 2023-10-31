//
// Created by beafowl on 30/10/23.
//

#include "EwECS/Music/Music.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Music/MusicComponent.hpp"
#include "EwECS/World.hpp"
#include "SFML/Audio.hpp"

namespace ECS {
    sf::Music *Music::initMusic(const std::string &aPath)
    {
        auto &assetManager = ECS::Asset::AssetManager::getInstance();

        if (!assetManager.hasAsset<sf::Music *>(aPath)) {
            auto *music = new sf::Music();
            if (!music->openFromFile(aPath)) {
                Logger::error("Music not found: " + aPath);
                delete music;
                return nullptr;
            }
            assetManager.addAsset<sf::Music *>(aPath, music);
        }
        return assetManager.getAsset<sf::Music *>(aPath);
    }

    void Music::play(Component::MusicComponent &aMusicComponent)
    {
        if (aMusicComponent._music == nullptr) {
            return;
        }
        if (isPlaying(aMusicComponent) || aMusicComponent._state == Component::MUSIC_STATE::PLAYING) {
            return;
        }

        aMusicComponent._music->setLoop(aMusicComponent._loop);
        aMusicComponent._music->setVolume(aMusicComponent._volume);
        aMusicComponent._music->play();
        aMusicComponent._state = Component::MUSIC_STATE::PLAYING;
    }

    void Music::stop(Component::MusicComponent &aMusicComponent)
    {
        if (aMusicComponent._music == nullptr) {
            return;
        }
        aMusicComponent._music->stop();
        aMusicComponent._state = Component::MUSIC_STATE::STOP;
    }

    void Music::pause(Component::MusicComponent &aMusicComponent)
    {
        if (aMusicComponent._music == nullptr) {
            return;
        }
        aMusicComponent._music->pause();
        aMusicComponent._state = Component::MUSIC_STATE::PAUSE;
    }

    bool Music::isPlaying(Component::MusicComponent &aMusicComponent)
    {
        if (aMusicComponent._music == nullptr) {
            return false;
        }
        return aMusicComponent._music->getStatus() == sf::Music::Playing;
    }

    void Music::createMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic)
    {
        ECS::Music const &music = ECS::Music::getInstance();

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value() || musicComponent.value()._state != Component::MUSIC_STATE::UNKNOW) {
                continue;
            }
            musicComponent.value()._music = music.initMusic(musicComponent.value()._path);
            if (musicComponent.value()._music == nullptr) {
                Logger::error("Music not found: " + musicComponent.value()._path);
                continue;
            }
            musicComponent.value()._state = Component::MUSIC_STATE::STOP;
        }
    }

    void Music::playMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic)
    {
        ECS::Music const &music = ECS::Music::getInstance();

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value() || musicComponent.value()._music == nullptr
                || musicComponent.value()._state == Component::MUSIC_STATE::UNKNOW) {
                continue;
            }
            music.play(musicComponent.value());
        }
    }

    void Music::stopMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic)
    {
        ECS::Music const &music = ECS::Music::getInstance();

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value() || musicComponent.value()._music == nullptr
                || musicComponent.value()._state == Component::MUSIC_STATE::UNKNOW) {
                continue;
            }
            if ((musicComponent.value()._state == Component::MUSIC_STATE::STOP
                 && musicComponent.value()._music->getStatus() == sf::Sound::Playing)
                || (musicComponent.value()._state == Component::MUSIC_STATE::PAUSE
                    && musicComponent.value()._music->getStatus() == sf::Sound::Paused)) {
                musicComponent.value()._state = Component::MUSIC_STATE::STOP;
                music.stop(musicComponent.value());
            }
        }
    }

    void Music::pauseMusic(ECS::Core::SparseArray<Component::MusicComponent> &aMusic)
    {
        ECS::Music const &music = ECS::Music::getInstance();

        for (auto &musicComponent : aMusic) {
            if (!musicComponent.has_value() || musicComponent.value()._music == nullptr
                || musicComponent.value()._state == Component::MUSIC_STATE::UNKNOW) {
                continue;
            }
            if (musicComponent.value()._state == Component::MUSIC_STATE::PAUSE
                && musicComponent.value()._music->getStatus() == sf::Sound::Playing) {
                musicComponent.value()._state = Component::MUSIC_STATE::PAUSE;
                music.pause(musicComponent.value());
            }

        }
    }
} // namespace ECS
