//
// Created by beafowl on 31/10/23.
//

#include "EwECS/Sound/SoundPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Sound/SoundComponent.hpp"
#include "EwECS/Sound/Sound.hpp"
#include "EwECS/World.hpp"

namespace ECS {
    void SoundPluginConfig::load(const std::string &aJsonPath)
    {
        auto &configReader = ConfigReader::getInstance();
        try {
            auto &soundConf = configReader.loadConfig(aJsonPath)["sound"];

            _configPath = aJsonPath;
        } catch (std::exception &e) {
            Logger::error("Failed to load sound config: " + std::string(e.what()));
        }
    }

    SoundPluginConfig::SoundPluginConfig() = default;

    SoundPluginConfig &SoundPluginConfig::getInstance()
    {
        static SoundPluginConfig instance;

        return instance;
    }

    SoundPluginConfig::~SoundPluginConfig() = default;

    SoundPlugin::SoundPlugin() = default;

    SoundPlugin::~SoundPlugin() = default;

    void SoundPlugin::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager)
    {
        try {
            aWorld.registerComponent<Component::SoundComponent>();
        } catch (std::exception &e) {
            Logger::error("Sound already registered");
        }
        try {
            aAssetManager.registerAssetHandler<sf::SoundBuffer *>();
        } catch (std::exception &e) {
            Logger::error("Sound buffer already registered");
        }
        aWorld.addSystem<Component::SoundComponent>(ECS::Sound::createSound);
        aWorld.addSystem<Component::SoundComponent>(ECS::Sound::playSound);
        aWorld.addSystem<Component::SoundComponent>(ECS::Sound::stopSound);
        aWorld.addSystem<Component::SoundComponent>(ECS::Sound::pauseSound);
    }
} // namespace ECS::Sound
