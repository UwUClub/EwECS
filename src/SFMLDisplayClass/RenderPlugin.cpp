#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "EwECS/World.hpp"
#include "SFML/Graphics/Texture.hpp"

void ECS::Render::RenderPluginConfig::load(const std::string &aJsonPath)
{
    auto &configReader = ConfigReader::getInstance();
    configReader.loadConfig(aJsonPath);
    try {
        auto &graphicsConf = configReader.get(aJsonPath)["graphics"];

        _windowName = graphicsConf["name"];
        _windowWidth = graphicsConf["width"];
        _windowHeight = graphicsConf["height"];
        _configPath = aJsonPath;
    } catch (std::exception &e) {
        std::cerr << "Failed to load config: " << e.what() << std::endl;
        _windowName = "R-Type";
        _windowWidth = 1920;
        _windowHeight = 1080;
        _configPath = "";
    }
}

ECS::Render::RenderPluginConfig::RenderPluginConfig()
    : _windowWidth(0),
      _windowHeight(0)
{
    load(RENDER_PLUGIN_CONFIG_BASE);
}

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
    aWorld.registerComponent<Component::LoadedSprite>();

    aAssetManager.registerAssetHandler<sf::Texture *>();
}
