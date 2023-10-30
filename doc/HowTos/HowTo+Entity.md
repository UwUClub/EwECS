# How To Use The ECS
## Contents
- [Create a Component](#create-a-component)
- [Create a System](#create-a-system)
- [Add the Component to the World](#add-the-component-to-the-world)
- [Add the System to the World](#add-the-system-to-the-world)
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

    // Register the Position component
    world.registerComponent<Position>();
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
    return 0;
}
```
### Add a Component to an Entity
## Using a created Component
To add a `Component` to an `Entity`, you can call the `insertAt` method of the `SparseArray` with the `Entity` and the `Component` as parameters.
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

    auto positionComponent = Position(0, 0);

    // Add a position to the entity
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
Read the full documentation of the ECS on our [website](https://uwuclub.github.io/R-Type/).
