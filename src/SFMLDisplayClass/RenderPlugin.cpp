#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/Logger.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "EwECS/SFMLDisplayClass/SFMLDisplayClass.hpp"
#include "EwECS/World.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Utils.hpp"

void ECS::Render::RenderPluginConfig::load(const std::string &aJsonPath)
{
    auto &configReader = ConfigReader::getInstance();
    try {
        auto &graphicsConf = configReader.loadConfig(aJsonPath)["graphics"];

        _windowName = graphicsConf["name"];
        _windowWidth = graphicsConf["width"];
        _windowHeight = graphicsConf["height"];

        if (!_font.loadFromFile(graphicsConf["font"])) {
            Logger::warning("Failed to load font: " + graphicsConf["font"].get<std::string>());
        } else {
            _isFontLoaded = true;
            Logger::info("Font loaded: " + graphicsConf["font"].get<std::string>());
        }

        _configPath = aJsonPath;
    } catch (std::exception &e) {
        Logger::error("Failed to load graphics config: " + std::string(e.what()));
    }
}

ECS::Render::RenderPluginConfig::RenderPluginConfig()
    : _windowName("ECS"),
      _windowWidth(1920),
      _windowHeight(1080),
      _isFontLoaded(false)
{}

ECS::Render::RenderPluginConfig &ECS::Render::RenderPluginConfig::getInstance()
{
    static RenderPluginConfig instance;

    return instance;
}

ECS::Render::RenderPluginConfig::~RenderPluginConfig() = default;

ECS::Render::RenderPlugin::RenderPlugin() = default;

ECS::Render::RenderPlugin::~RenderPlugin() = default;

void ECS::Render::RenderPlugin::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager)
{
    try {
        aWorld.registerComponent<Component::LoadedSprite>();
    } catch (std::exception &e) {
        Logger::error("Loaded sprite already registered");
    }
    try {
        aWorld.registerComponent<Component::TextComponent>();
    } catch (std::exception &e) {
        Logger::error("Text component already registered");
    }

    aWorld.addSystem<Component::LoadedSprite, ECS::Utils::Vector2f>(ECS::SFMLDisplayClass::displayEntities);
    aWorld.addSystem<Component::TextComponent, ECS::Utils::Vector2f>(ECS::SFMLDisplayClass::displayTexts);
    aWorld.addSystem<Component::LoadedSprite>(ECS::SFMLDisplayClass::loadTextures);
    aWorld.addSystem(ECS::SFMLDisplayClass::getInput);
    aWorld.addSystem(ECS::SFMLDisplayClass::display);

    aAssetManager.registerAssetHandler<sf::Texture *>();
}
