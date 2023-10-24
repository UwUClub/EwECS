#include "EwECS/World.hpp"
#include <cstddef>

ECS::Core::World &ECS::Core::World::getInstance()
{
    static World instance;

    return instance;
}

void ECS::Core::World::killEntity(const std::size_t &aIdx)
{
    for (auto &component : _components) {
        _eraseFunctions[component.first](*this, aIdx);
    }
    _reusableIds.push_back(aIdx);
}

size_t ECS::Core::World::createEntity()
{
    if (_reusableIds.empty()) {
        const auto idx = _id;
        for (auto &component : _components) {
            _addFunctions[component.first](*this, idx);
        }

        _id++;
        return idx;
    }
    auto &idx = _reusableIds.front();

    _reusableIds.erase(_reusableIds.begin());
    for (auto &component : _components) {
        _addFunctions[component.first](*this, idx);
    }
    return idx;
}

void ECS::Core::World::runSystems()
{
    for (auto &system : _systems) {
        system();
    }
}

bool ECS::Core::World::isRunning() const
{
    return _isRunning;
}

void ECS::Core::World::stop()
{
    _isRunning = false;
}

void ECS::Core::World::start()
{
    _isRunning = true;
}

void ECS::Core::World::calcDeltaTime()
{
    {
        auto now = std::chrono::steady_clock::now();
        _delta = now - _lastTime;
        _lastTime = now;
    }
}

float ECS::Core::World::getDeltaTime() const
{
    return _delta.count();
}
