# How To Use The ECS
## Contents
- [What is an Asset](#what-is-an-asset)
- [Get the instance of the AssetManager](#get-the-instance-of-the-assetmanager)
- [Register a type of Asset](#register-a-type-of-asset)
- [Add an Asset](#add-an-asset)
- [Get an Asset](#get-an-asset)
- [Remove an Asset](#remove-an-asset)
- [Remove all Assets](#remove-all-assets)
- [Check if an Asset exists](#check-if-an-asset-exists)
- [Conclusion](#conclusion)

## How to use the Assets
### What is an Asset
- An `Asset` is a simple ressource for data, from textures to sounds or anything you want to load.
- The AssetManager aims to be a simple way to load and store assets. it will also destroy the assets when the `AssetManager` is destroyed.

### Get the instance of the AssetManager
To get the instance of the `AssetManager`, you need to call the `getInstance` method of the `AssetManager`.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();
    return 0;
}
```

### Register a type of Asset
To register a type of asset you need to call the `registerAssetHandler` method of the `AssetManager`. This method is especially useful if you want to load a custom type of deleter for this type of asset.
```cpp
#include "AssetManager.hpp"

void deleteTexture(sf::Texture *texture)
{
    delete texture;
}

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset, use base destroyer which is delete if none is provided.
    assetManager.registerAssetHandler<sf::Music *>();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>(deleteTexture);
    return 0;
}
```

### Add an Asset
To add an asset you need to call the `addAsset` method of the `AssetManager`. You need to load the asset before adding it to the `AssetManager`.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>(deleteTexture);

    // Load the asset
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("path/to/texture.png");

    // Add the asset to the AssetManager, the path is used as a key to retrieve the asset. You can now use the assetManager.getAsset method to retrieve the asset.
    assetManager.addAsset<sf::Texture *>("path/to/texture.png", texture);
    return 0;
}
```

### Get an Asset
To get an asset you need to call the `getAsset` method of the `AssetManager`. You need to load the asset before adding it to the `AssetManager`. It returns a reference to the asset.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>();

    // Load the asset
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("path/to/texture.png");

    // Add the asset to the AssetManager, the path is used as a key to retrieve the asset. You can now use the assetManager.getAsset method to retrieve the asset.
    assetManager.addAsset<sf::Texture *>("path/to/texture.png", texture);

    // Get the asset
    auto &texture = assetManager.getAsset<sf::Texture *>("path/to/texture.png");
    return 0;
}
```

### Remove an Asset
To remove an asset you need to call the `removeAsset` method of the `AssetManager`.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>();

    // Load the asset
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("path/to/texture.png");

    // Add the asset to the AssetManager, the path is used as a key to retrieve the asset. You can now use the assetManager.getAsset method to retrieve the asset.
    assetManager.addAsset<sf::Texture *>("path/to/texture.png", texture);

    // Remove the asset, it will call the deleter of the asset.
    assetManager.removeAsset<sf::Texture *>("path/to/texture.png");
    return 0;
}
```

### Remove all Assets
To remove all assets of a type you need to call the `clearAssets` method of the `AssetManager`.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>();

    // Load the asset
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("path/to/texture.png");

    // Add the asset to the AssetManager, the path is used as a key to retrieve the asset. You can now use the assetManager.getAsset method to retrieve the asset.
    assetManager.addAsset<sf::Texture *>("path/to/texture.png", texture);

    // Remove all assets of this type, it will call the deleter of the asset.
    assetManager.clearAssets<sf::Texture *>();
    return 0;
}
```

### Check if an Asset exists
To check if an asset exists you need to call the `hasAsset` method of the `AssetManager`.
```cpp
#include "AssetManager.hpp"

int main(void)
{
    // Get the instance of the AssetManager
    ECS::Core::AssetManager &assetManager = ECS::Core::AssetManager::getInstance();

    // Register a type of asset with a custom deleter, here we use a simple delete but it's our funcionn that is going to be called.
    assetManager.registerAssetHandler<sf::Texture *>();

    // Load the asset
    sf::Texture *texture = new sf::Texture();
    texture->loadFromFile("path/to/texture.png");

    // Add the asset to the AssetManager, the path is used as a key to retrieve the asset. You can now use the assetManager.getAsset method to retrieve the asset.
    assetManager.addAsset<sf::Texture *>("path/to/texture.png", texture);

    // Check if the asset exists
    if (assetManager.hasAsset<sf::Texture *>("path/to/texture.png")) {
        std::cout << "The asset exists" << std::endl;
    }
    return 0;
}
```

### Conclusion
The `AssetManager` is a simple way to load and store assets. It will also destroy the assets when the `AssetManager` is destroyed.
Use it for every type of asset you want to load once and use everywhere in your program.
