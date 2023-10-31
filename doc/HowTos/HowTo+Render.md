# How to Use The ECS
## Contents
 - [What does the plugin do](#what-does-the-plugin-do)
 - [Add the plugin to your program](#add-the-plugin-to-your-program)
 - [Configure the window](#configure-the-window)
 - [Use your own json file to create entity](#use-your-own-json-file-to-create-entity)

## How to use the Render plugin
### What does the plugin do
 - The Render plugin will permit to your program to have a visual window with 2D animated sprites and texts using the SFML library.
 - The Render plugin will also handle keyboard and mouse input.

### Add the plugin to your program
In your main program you need to use the `plug` function to register the plugin in your program.
The `plug` function will register all the necessary components and system by hitself no need to do it after.
If you compile the following code you will see a empty black window (1920*1080) named ECS.

```cpp
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/World.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
    
    // Get the instance of the render plugin
    ECS::Render::RenderPlugin renderPlugin;

    //Plug the plugin
    renderPlugin.plug(world, assetManager);

    return 0;
}
```

### Configure the window
 - If you want a window with your own dimensions and name you simply need to add the following line before the `plug` function to the precedent code : 
                "ECS::Render::RenderPluginConfig::getInstance().load("`Your configuration file path`");"

```cpp
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/World.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
    
    // Get the instance of the Render plugin
    ECS::Render::RenderPlugin renderPlugin;

    // Get the instance of the RenderPluginConfig and load the configuration file
    ECS::Render::RenderPluginConfig::getInstance().load("Your configuration file path");

    //Plug the plugin
    renderPlugin.plug(world, assetManager);

    return 0;
}
```
 - The configuration file needs to be json and constructed with the following variable :
```json
{
    "graphics": {
        "name": "Your window name", // This will be the name of your window
        "width": 1920, // This will be the width of your window
        "height": 1080, // This will be the height of your window
        "font": "assets/font.ttf" // This will be the font used for all your texts
    }
}
```

### Use your own json file to create entity
 - To create your you need to get the list of `LoadedSprite` components first the add your own LoadedSprite to the list.
 - Once it has been added to the list your entity will be handle by the program.

```cpp
#include "EwECS/SFMLDisplayClass/RenderPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/World.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
    
    // Get the instance of the Render plugin
    ECS::Render::RenderPlugin renderPlugin;

    // Get the instance of the RenderPluginConfig and load the configuration file
    ECS::Render::RenderPluginConfig::getInstance().load("Your configuration file path");

    // Plug the plugin
    renderPlugin.plug(world, assetManager);

    // Get the list of the LoadedSprite
    auto &sprite = world.getComponent<Component::LoadedSprite>();

    // Create a empty entity
    const size_t idx = world.createEntity();

    // Insert the entity with his sprite
    sprite.insertAt(idx, Component::LoadedSprite{"Your configuration file"});
    return 0;
}
```
 - The configuration file needs to be json and constructed with the following variable :
```json
{
    "path": "assets/sprites/r-typesheet42.png", // The path to your asset texture
    "scale": 1, // The number by whiwh you want to scale your texture (1 is the normal size)
    "rects": { // The list of all the frame you need to make your sprite animated
        "frame1": { // The first frame
            "top": 0, // The top position of your frame in your asset
            "left": 0, // The left position of your frame in your asset
            "width": 33, // The width of your frame in your asset
            "height": 17, // The height of your frame in your asset
            "time": 0.2 // The duration of the frame
        },
        "frame2": { // The second frame
            "top": 0,
            "left": 33,
            "width": 33,
            "height": 17,
            "time": 0.2
        },
        "frame3": { // The third frame
            "top": 0,
            "left": 66,
            "width": 33,
            "height": 17,
            "time": 0.2
        },
        "frame4": { // The fourth frame
            "top": 0,
            "left": 99,
            "width": 33,
            "height": 17,
            "time": 0.2
        },
        "frame5": { // The fifth frame
            "top": 0,
            "left": 132,
            "width": 33,
            "height": 17,
            "time": 0.2
        }
    }
}
```