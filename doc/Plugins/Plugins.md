# What is a plugin
## Contents
- [What is a plugin](#what-is-a-plugin)
- [How to create a plugin](#how-to-create-a-plugin)
    - [The Plug method of the IPlugin](#the-plug-method-of-the-iplugin)
    - [The Unload method of the IPlugin](#the-unload-method-of-the-iplugin)
    - [The IConfigPlugin](#the-iconfigplugin)
- [How to use a plugin](#how-to-use-a-plugin)
- [Conclusion](#conclusion)

## What is a plugin
- A plugin is a way to add features to the ECS.
- A plugin is a class that can inherits from the `IPlugin` class.
- A plugin can add components, systems, events, entities, assets, etc.
- A plugin can be loaded and unloaded at runtime.
- It aims to add features to the you program easily.

## How to create a plugin
- To create a plugin, it's recommended to create a class that inherits from the `IPlugin` class.
- An `IPlugin` can use a `IConfigPlugin` which is a class that can be used to configure the plugin, it contains settings for the plugin, they can be changed through JSON files.

### The Plug method of the IPlugin
- The `Plug` method is called to integrate the plugin to your application.
- The `Plug` method is called with the `World` and the `AssetManager` as parameters.
- It will simply add the components, systems, events, entities, assets, etc. to the `World` and the `AssetManager`.

### The Unload method of the IPlugin
- To `unload` a plugin, you have to remove the different parts of it from the `World` and the `AssetManager`.

### The IConfigPlugin
- Has a `load` method that takes a path to a `JSON` file as parameter.
- The `load` method will load the settings from the `JSON` file.
- Contains base settings for the plugin.

## How to use a plugin
Here is an example of how to use the `RenderPlugin`:
```cpp
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();

    // Get the instance of the Render plugin
    ECS::Render::RenderPlugin renderPlugin;

    // Load new settings for the plugin
    ECS::Render::RenderPluginConfig::getInstance().load("path-to-settings.json");

    //Plug the plugin
    renderPlugin.plug(world, assetManager);

    // Once done, you can use every component the plugin provides to make it works
    // For example, you can create a new entity with a LoadedSprite component

    return 0;
}
```

## Conclusion
- A plugin is a way easy to add features to the ECS.
- Can be developed by anyone.
- Give a look to the plugins we provide to see how to create one.
- Check the documentation of each plugins for more informations:
    - [Physic](./Physic.md)
    - [Render](./Render.md)
    - [Network](./Network.md)
    - [Sound](./Sound.md)
    - [Music](./Music.md)

