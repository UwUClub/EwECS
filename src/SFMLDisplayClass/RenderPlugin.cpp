#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "EwECS/ConfigReader/ConfigReader.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "EwECS/World.hpp"


void ECS::Render::RenderPluginConfig::load(const std::string &aJsonPath)
{
    auto &configReader = ConfigReader::getInstance();
    configReader.loadConfig(aJsonPath);
    try {
        auto &graphicsConf = configReader.get()["graphics"];

        _windowName = graphicsConf["name"];
        _windowWidth = graphicsConf["width"];
        _windowHeight = graphicsConf["height"];
    } catch (std::exception &e) {
        std::cerr << "Failed to load config: " << e.what() << std::endl;
        _windowName = "R-Type";
        _windowWidth = 1920;
        _windowHeight = 1080;
    }
}

ECS::Render::RenderPluginConfig::RenderPluginConfig(const std::string &aJsonPath)
{
    load(aJsonPath);
}

ECS::Render::RenderPluginConfig::~RenderPluginConfig() = default;

ECS::Render::RenderPlugin::RenderPlugin()
    : _config(RENDER_PLUGIN_CONFIG_BASE)
{}

ECS::Render::RenderPlugin::RenderPlugin(ECS::Render::RenderPluginConfig &aConfig)
    : _config(aConfig)
{}

ECS::Render::RenderPlugin::~RenderPlugin() = default;

void ECS::Render::RenderPlugin::plug(ECS::Core::World &aWorld, ECS::Asset::AssetManager &aAssetManager)
{
    aWorld.registerComponent<Component::LoadedSprite>();

    aAssetManager.registerAssetHandler<sf::Texture *>();
}
