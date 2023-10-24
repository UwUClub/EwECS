//
// Created by beafowl on 24/10/23.
//

#include "SoundEvent.hpp"

namespace ECS::Event {
    // -------------------CONSTRUCTORS / DESTRUCTOR-------------------//
    SoundEvent::SoundEvent(const SoundEventType &aSoundEventType, const SoundType &aSoundType, const SoundState &aSoundState)
        : _soundEventType(aSoundEventType),
          _soundState(aSoundState),
          _soundType(aSoundType)
    {}
}
