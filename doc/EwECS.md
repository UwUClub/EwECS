# What is the EwECS
## Contents
- [Introduction](#introduction)
- [ECS in the Engine](#ecs-in-the-engine)
- [How to use the ECS](#how-to-use-the-ecs)
- [Conclusion](#conclusion)

## Introduction
ECS stands for Entity Component System. It is a design pattern used in game development to organize entities (such as characters, objects, etc.) and their behaviors. In an ECS, entities are composed of one or more components, which define their properties and behaviors. Systems are then used to process the entities and their components, updating their state and behavior over time. This approach can make game development more modular and flexible, allowing for easier reuse of code and more efficient processing of game entities.

## ECS in the Engine
- The ECS in the engine is a very simple implementation of the ECS design pattern.
- It is composed of three main parts: the `Entity`, the `Component`, and the `System`.
- The `Entity` is a simple container for `Component`s.
- The `Component` is a simple container for data.
- The `System` is a simple container for logic.
- The `System` is responsible for processing the `Component`s of an `Entity` and updating their state and behavior.
- The `System` is also responsible for adding and removing `Component`s from an `Entity`.
- The `System` is also responsible for adding and removing `Entity`s from the ECS.
- Each `Component` is stored in a `SparseArray`, the index of each row in the array represent the `Entity`.
- A `SparseArray` is an array containing the `Component`, it is a an array of *optional values*.
- The `Components` are data's struct that can be registered in the `World`.
- The `Systems` are functions that can be registered in the `World`, it need to have the component's type that it will process as template parameter.
- The `World` is the main class of the ECS, it is the container of the `SparseArray` of `Components` and `Systems`.

## How to use the ECS
Refer to the [HowTo.md](./HowTos/HowTo.md) file.

## Conclusion
- The ECS is a very simple implementation of the ECS design pattern.
- Is is very easy to use and to understand.
- It is very fast.
- It is very flexible.
- It is very modular.
