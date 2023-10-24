#include "AssetManager.hpp"

ECS::Asset::AssetManager &ECS::Asset::AssetManager::getInstance() noexcept
{
    static AssetManager instance;

    return instance;
}
