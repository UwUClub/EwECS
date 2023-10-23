#include "AssetManager.hpp"

ECS::Asset::AssetManager &ECS::Asset::AssetManager::getInstance()
{
    static AssetManager instance;

    return instance;
}
