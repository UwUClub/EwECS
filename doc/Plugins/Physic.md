# How to Use The ECS
## Contents
- [What does the plugin do](#what-does-the-plugin-do)
- [Add the plugin to your program](#add-the-plugin-to-your-program)
- [Configure the settings](#configure-the-settings)
- [How to use the systems](#how-to-use-the-systems)
- [Components](#components)
- [Conclusion](#conclusion)

## How to use the Physic plugin
### What does the plugin do
 - The physic plugin will check for collision and add a gravity to your entities.

### Add the plugin to your program
In your main program you need to use the `plug` function to register the plugin in your program.
The `plug` function will register all the necessary components and system by hitself no need to do it after.

```cpp
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/World.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();

    // Get the instance of the physic plugin
    ECS::Physic::PhysicPlugin physicPlugin;

    //Plug the plugin
    physicPlugin.plug(world, assetManager);

    return 0;
}
```

### Configure the settings
 - If you want to change the base settings, you simply need to add the following line before the `plug` function to the precedent code : 
                "ECS::Physic::PhysicPluginConfig::getInstance().load("`Your configuration file path`");"

```cpp
#include "EwECS/Physic/PhysicPlugin.hpp"
#include "EwECS/Asset/AssetManager.hpp"
#include "EwECS/World.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Get the instance of the assets manager
    ECS::Asset::AssetManager &assetManager = ECS::Asset::AssetManager::getInstance();
    
    // Get the instance of the Physic plugin
    ECS::Physic::RenderPlugin physicPlugin;

    // Get the instance of the PhysicPluginConfig and load the configuration file
    ECS::Physic::PhysicPluginConfig::getInstance().load("Your configuration file path");

    //Plug the plugin
    physicPlugin.plug(world, assetManager);

    return 0;
}
```
 - The configuration file needs to be json and constructed with the following variable :
```json
{
    "physics": {
        "gravity": 2, // The gravity factor
        "initial_fall_velocity": 2 // The initial fall velocity of the entity
    }
}
```

### How to use the systems
- To check for collisions, you simply need to add the `HitBox` component to your entity.
- To add the gravity to your entity, you simply need to add the `Weight` component to your entity. If your entity doesn't have it, it will not fall.

### Components
- `HitBox` : This component is used to check for collisions.
```cpp
            HitBox(float aWidth, float aHeight)
                : width(aWidth),
                  height(aHeight),
                  isColliding(false)
            {}
            float width; // The width of the hitbox
            float height; // The height of the hitbox
            bool isColliding; // A boolean to know if the entity is colliding
            std::vector<std::size_t> collidingId; // A vector of the id of the entities colliding with this entity
```
- `Weight` : This component is used to add a gravity to your entity.
```cpp
            Weight(float aWeight, float aFallVelocity)
                : weight(aWeight),
                  initialFallVelocity(aFallVelocity),
                  fallVelocity(aFallVelocity)
            {}
            float weight; // The weight of the entity
            float initialFallVelocity; // The initial fall velocity of the entity
            float fallVelocity; // The current fall velocity of the entity
```

### Conclusion
- The physic plugin is a simple way to add a gravity and collision to your entities.
- Use it for your games that need a gravity and collision system.