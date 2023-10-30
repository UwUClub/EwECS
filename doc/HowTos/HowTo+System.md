# How To Use The ECS
## Contents
- [What is a System](#what-is-a-system)
- [Create a System](#create-a-system)
- [Add the System to the World](#add-the-system-to-the-world)
- [Run the Systems](#run-the-systems)
- [Conclusion](#conclusion)

## How to use the ECS
### What is a System
- A `System` is a simple container for logic.
- It's a function that can be registered in the `World`.

### Create a System
To create a `System`, you need to create a function. (I recommend to use a static function in an abstract class), the arguments of the function are the `SparseArray` of the `Component`s that the `System` will process.
(cf [HowTo+Component.md](./HowTo+Component.md))
```cpp
void updatePosition(ECS::SparseArray<Position> &aPositionArray)
{
    for (auto &position : aPositionArray)
    {
        // Check if the entity has a position
        if (!position.hasValue()) {
            continue;
        }
        // Update the position if one is found
        position.value().x += 1;
        position.value().y += 1;
    }
}

void updateHP(ECS::SparseArray<HP> &aHPArray, ECS::SparseArray<Damage> &aDamageArray)
{
    for (auto &hp : aHPArray)
    {
        // Check if the entity has a HP
        if (!hp.hasValue()) {
            continue;
        }
        // Check if the entity has a Damage
        if (!aDamageArray[hp.index()].hasValue()) {
            continue;
        }
        // Update the HP if one is found using the entity own damage (clearly made for example purpose)
        hp.value().hp -= aDamageArray[hp.index()].value().damage;
    }
}
```
### Add the System to the World
To add a `System` to the `World`, you need to call the `registerSystem` method of the `World` with the `System` as parameter, it need to have the `Component`'s type that it will process as template parameter.
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
    return 0;
}
```
### Run the Systems
To run the `System`s, you need to call the `runSystems` method of the `World` with the `Component`'s type that it will process as template parameter.
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

    // Here we start the game loop, the world will run the systems until the world is not running anymore
    while (world.isRuning()) {
        // run all the systems that are registered in the world
        world.runSystems();
        // Update the world delta time
        world.calcDeltaTime();
    }

    return 0;
}
```

## Conclusion
This is just some example of how to use the ECS, you can use it as you want.
