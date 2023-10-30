# How To Use The ECS
## Contents
- [What is a Component](#what-is-a-component)
- [Create a Component](#create-a-component)
- [Add the Component to the World](#add-the-component-to-the-world)
- [Add a Component to an Entity](#add-a-component-to-an-entity)
- [Conclusion](#conclusion)

## How to use the ECS
### What is a Component
- A `Component` is a simple container for data.
- It's a struct that can be registered in the `World`.
- It's like an array of *optional values*.
- The index in the array represent the `Entity`.

### Create a Component
To create a `Component`, you need to create a struct.
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

### Add the Component to the World
To add a `Component` to the `World`, you need to call the `registerComponent` method of the `World` with the `Component` type as template parameter.
```cpp
#include "Components.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Register the HP component
    world.registerComponent<HP>();
    // Register the Damage component
    world.registerComponent<Damage>();
    return 0;
}
```

### Add a Component to an Entity
## Using a created Component
To add a `Component` to an `Entity`, you can call the `insertAt` method of the `SparseArray` with the `Entity` and the `Component` as parameters, you need to register the `Component` in the `World` before.
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
### Get a Component
```cpp
#include "Components.hpp"

int main(void)
{
    // Get the instance of the World
    ECS::Core::World &world = ECS::Core::World::getInstance();

    // Register the Position component
    world.registerComponent<Position>();
    // Get the Position component
    auto &position = world.getComponent<Position>(entity);

    return 0;
}
```
## Conclusion
This is just some example of how to use the components, you can use it as you want.
