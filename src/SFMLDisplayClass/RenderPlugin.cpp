#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "EwECS/World.hpp"

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
