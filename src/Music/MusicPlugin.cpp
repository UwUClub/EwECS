//
// Created by beafowl on 31/10/23.
//

#include "EwECS/Music/MusicComponent.hpp"
#include "EwECS/Music/MusicPlugin.hpp"
#include "EwECS/Music/Music.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/World.hpp"

namespace ECS {
    MusicPlugin::MusicPlugin() = default;

    MusicPlugin::~MusicPlugin() = default;

    void MusicPlugin::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager)
    {
        try {
            aWorld.registerComponent<Component::MusicComponent>();
        } catch (std::exception &e) {
            Logger::error("Music already registered");
        }
        try {
            aAssetManager.registerAssetHandler<sf::Music *>();
        } catch (std::exception &e) {
            Logger::error("Music buffer already registered");
        }
        aWorld.addSystem<Component::MusicComponent>(ECS::Music::createMusic);
        aWorld.addSystem<Component::MusicComponent>(ECS::Music::playMusic);
        aWorld.addSystem<Component::MusicComponent>(ECS::Music::stopMusic);
        aWorld.addSystem<Component::MusicComponent>(ECS::Music::pauseMusic);
    }
}
