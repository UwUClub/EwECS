#include "EwECS/Physic/PhysicPlugin.hpp"
#include <cstddef>
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/Physic/HitBox.hpp"
#include "EwECS/Physic/Weight.hpp"
#include "EwECS/Utils.hpp"
#include "EwECS/World.hpp"

void ECS::Physic::PhysicPluginConfig::load(const std::string &aJsonPath)
{
    auto &configReader = ConfigReader::getInstance();
    try {
        auto &physicConf = configReader.loadConfig(aJsonPath)["physics"];

        _configPath = aJsonPath;
        _gravity = static_cast<float>(physicConf["gravity"]);
        _initialJumpVelocity = static_cast<float>(physicConf["initial_fall_velocity"]);

    } catch (std::exception &e) {
        std::cerr << "Failed to load config: " << e.what() << std::endl;
    }
}

ECS::Physic::PhysicPluginConfig::PhysicPluginConfig()
    : _gravity(2),
      _initialJumpVelocity(2)
{}

ECS::Physic::PhysicPluginConfig &ECS::Physic::PhysicPluginConfig::getInstance()
{
    static PhysicPluginConfig instance;

    return instance;
}

ECS::Physic::PhysicPluginConfig::~PhysicPluginConfig() = default;

ECS::Physic::PhysicPlugin::PhysicPlugin() = default;

ECS::Physic::PhysicPlugin::~PhysicPlugin() = default;

void ECS::Physic::PhysicPlugin::checkCollision(ECS::Core::SparseArray<ECS::Utils::Vector2f> &aPos,
                                               ECS::Core::SparseArray<Component::HitBox> &aHitBox)
{
    auto size = aPos.size();

    for (size_t idx = 0; idx < size; idx++) {
        if (!aPos[idx].has_value() || !aHitBox[idx].has_value()) {
            continue;
        }
        auto &pos = aPos[idx].value();
        auto &hitBox = aHitBox[idx].value();

        for (size_t idx2 = 0; idx2 < size; idx2++) {
            if (!aPos[idx2].has_value() || !aHitBox[idx2].has_value()) {
                continue;
            }
            auto &pos2 = aPos[idx2].value();
            auto &hitBox2 = aHitBox[idx2].value();

            if (hitBox.isColliding) {
                hitBox.isColliding = false;
                hitBox.collidingId.clear();
            }

            if (pos.x <= pos2.x + hitBox2.width && pos.x + hitBox.width >= pos2.x && pos.y <= pos2.y + hitBox2.height
                && pos.y + hitBox.height >= pos2.y) {
                hitBox.isColliding = true;
                hitBox.collidingId.push_back(idx2);
                hitBox2.isColliding = true;
                hitBox2.collidingId.push_back(idx);
            }
        }
    }
}

void ECS::Physic::PhysicPlugin::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager & /*aAssetManager*/)
{
    try {
        aWorld.registerComponent<Component::HitBox>();
    } catch (std::exception &e) {
        Logger::error(e.what());
    }
    try {
        aWorld.registerComponent<Component::Weight>();
    } catch (std::exception &e) {
        Logger::error(e.what());
    }
    try {
        aWorld.registerComponent<Utils::Vector2f>();
    } catch (std::exception &e) {
        Logger::error(e.what());
    }

    aWorld.addSystem<ECS::Utils::Vector2f, Component::HitBox>(checkCollision);
    aWorld.addSystem<ECS::Utils::Vector2f, Component::Weight>(applyGravity);
}

void ECS::Physic::PhysicPlugin::applyGravity(Core::SparseArray<Utils::Vector2f> &aPos,
                                             Core::SparseArray<Component::Weight> &aWeight)
{
    auto &world = Core::World::getInstance();
    auto &config = PhysicPluginConfig::getInstance();
    auto size = aPos.size();

    for (size_t i = 0; i < size; i++) {
        if (!aWeight[i].has_value() || !aPos[i].has_value()) {
            continue;
        }
        auto &weight = aWeight[i].value();
        auto &pos = aPos[i].value();

        pos.y += (weight.weight * weight.fallVelocity) * world.getDeltaTime();
        weight.fallVelocity += config._gravity * world.getDeltaTime();
    }
}
