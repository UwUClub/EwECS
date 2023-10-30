# How To Use The ECS
## Contents
- [What is an Entity](#what-is-an-entity)
- [Create an Entity](#create-an-entity)
- [Add a Component to an Entity](#add-a-component-to-an-entity)
- [Kill an Entity](#kill-an-entity)
- [Conclusion](#conclusion)

## How to use the ECS
### Prerequisites
> You need to understand how to use [Component](./HowTo+Component.md) and [System](./HowTo+System.md).
### What is an Entity
- An `Entity` doesn't exist in the ECS, it's just a number, it's the index in the `Component` (`SparseArray`) that represent the entity.

### Create an Entity
To create an `Entity`, you need to call the `createEntity` method of the `World`.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Create an entity
    std::size_t entity = world.createEntity();
    return 0;
}
```
### Add a Component to an Entity
## Using a created Component
To add a `Component` to an `Entity`, you can call the `insertAt` method of the `SparseArray` with the `Entity` and the `Component` as parameters, you need to register the `Component` in the `World` before.
```cpp
// Components.hpp
// Here we create a simple Position component with two float
struct Position
{
    Position(float aX, float aY) : x(aX), y(aY) {}

    float x;
    float y;
};
// Here we create a simple HP component with two int
struct HP
{
    HP(int aHP) : hp(aHP), maxHp(aHP) {}

    int hp;
    int maxHp;
};
// Here we create a simple Damage component with an int
struct Damage
{
    Damage(int aDamage) : damage(aDamage) {}

    int damage;
};
```
```cpp
#include "Components.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    auto &positionSystem = world.registerComponent<Position>();

    // Create an entity
    std::size_t entity = world.createEntity();

    auto positionComponent = Position(0, 0);

    // Add a position component to the entity
    positionSystem.insertAt(entity, positionComponent);
    return 0;
}
```
## Using a the world
To add a `Component` to an `Entity`, you can use `emplaceAt` method of the `World` with the `Component` as template parameter, the `Entity` and the data to create the `Component` as parameters.
```cpp
#include "Components.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Create an entity
    std::size_t entity = world.createEntity();

    // Add a position to the entity
    world.emplaceEntityComponent<Position>(entity, 0, 0);
    return 0;
}
```

### Kill an Entity
To kill an `Entity`, you need to call the `killEntity` method of the `World` with the `Entity` as parameter.
It will automatically remove all the `Component`s of the `Entity` from the `World`.
```cpp
int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    auto &positionSystem = world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();

    // Register the updatePosition system
    world.registerSystem<Position>(updatePosition);
    // Register the updateHP system
    world.registerSystem<HP, Damage>(updateHP);

    // Create an entity
    std::size_t entity = world.createEntity();

    // Add a position to the entity
    world.emplaceEntityComponent<Position>(entity, 0, 0);
    world.emplaceEntityComponent<HP>(entity, 100);
    world.emplaceEntityComponent<Damage>(entity, 10);

    // Kill the entity
    world.killEntity(entity);
    return 0;
}
```
## Conclusion
This is just some example of how to use the ECS, you can use it as you want.
