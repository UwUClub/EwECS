# How To Use The ECS
## Contents
- [What is an Event](#what-is-an-event)
- [Get the instance of the EventManager](#get-the-instance-of-the-eventmanager)
- [Create a Event](#create-an-event)
- [Queue an Event](#queue-an-event)
- [Get an Event](#get-an-event)
- [Remove an Event](#remove-an-event)
- [Remove a list of Events](#remove-a-list-of-events)
- [Remove all Events](#remove-all-events)
- [Subscribe to an Event](#subscribe-to-an-event)
- [Unsubscribe to an Event](#unsubscribe-to-an-event)
- [Publish an Event](#publish-an-event)
- [Conclusion](#conclusion)

## How to use the Events
### What is an Event
- An event is a way to communicate between systems.
- An event is a struct.

### Get the instance of the EventManager
To get the instance of the `EventManager`, you need to call the `getInstance` method of the `EventManager`.
```cpp
#include "EventManager.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();
    return 0;
}
```

### Create an Event
To create an `Event`, you need to create a struct.
```cpp
// Events.hpp
// Here we create a simple DamageEvent event with an int
struct DamageEvent
{
    DamageEvent(int aDamage) : damage(aDamage) {}

    int damage;
};
```

### Queue an Event
To queue an `Event`, you need to call the `pushEvent` method of the `EventManager` with the `Event` as parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Queue the DamageEvent event
    eventManager.pushEvent<DamageEvent>(DamageEvent(42));
    return 0;
}
```

### Get an Event
To get an `Event`, you need to call the `getEventsByType` method of the `EventManager` with the `Event` as template parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Get all the queued DamageEvent events
    auto &events = eventManager.getEventsByType<DamageEvent>();
    return 0;
}
```

### Remove an Event
To remove an `Event`, you need to call the `removeEvent` method of the `EventManager` with the `Event` as template parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Index of the second event
    size_t eventIndex = 2;
    // Remove the event at index 2 of the DamageEvent events queue
    eventManager.removeEvent<DamageEvent>(eventIndex);
    return 0;
}
```

### Remove a list of Events
To remove a list of `Event`s, you need to call the `removeEvent` method of the `EventManager` with the `Event` as template parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Index of the second event
    std::vector<size_t> eventsIndexToRemove = {2, 3, 4};
    // Remove the event at index 2, 3 and 4 of the DamageEvent events queue
    eventManager.removeEvent<DamageEvent>(eventsIndexToRemove);
    return 0;
}
```

### Remove all Events
To remove all `Event`s, you need to call the `keepEventsAndClear` method of the `EventManager` with the `Event` as template parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Remove all the events except the DamageEvent events, you can put any event type and multiple types
    eventManager.keepEventsAndClear<DamageEvent>();

    // Remove all the events
    eventManager.keepEventsAndClear<>();
    return 0;
}
```

### Subscribe to an Event
To subscribe to an `Event`, you need to call the `subscribe` method of the `EventManager` with the `Event` as template parameter and a function as parameter.
```cpp
#include "Events.hpp"

// Here we create a simple function that will be called when a DamageEvent event is published
void onDamageEvent(const DamageEvent &event)
{
    std::cout << "DamageEvent event received with damage: " << event.damage << std::endl;
}

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Subscribe to the DamageEvent event
    eventManager.subscribe<DamageEvent>(onDamageEvent);
    return 0;
}
```

### Unsubscribe to an Event
To unsubscribe to an `Event`, you need to call the `unsubscribe` method of the `EventManager` with the `Event` as template parameter and a function as parameter.
```cpp
#include "Events.hpp"

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Subscribe to the DamageEvent event
    eventManager.unsubscribe<DamageEvent>(onDamageEvent);
    return 0;
}
```

### Publish an Event
To publish an `Event`, you need to call the `publish` method of the `EventManager` with the `Event` as parameter. It will call all the subscribed functions to this `Event`.
```cpp
#include "Events.hpp"

// Here we create a simple function that will be called when a DamageEvent event is published
void onDamageEvent(const DamageEvent &event)
{
    std::cout << "DamageEvent event received with damage: " << event.damage << std::endl;
}

int main(void)
{
    // Get the instance of the EventManager
    ECS::Core::EventManager *eventManager = ECS::Core::EventManager::getInstance();

    // Subscribe to the DamageEvent event
    eventManager.subscribe<DamageEvent>(onDamageEvent);

    // Publish the DamageEvent event, the onDamageEvent function will be called
    eventManager.publish<DamageEvent>(DamageEvent(42));
    return 0;
}
```

### Conclusion
You now know how to use the `EventManager` of the ECS.
It's very simple to use and very powerful.
You can create your own `Event`s and use them in your game, using subscriber and publisher or simple queue and get them.
