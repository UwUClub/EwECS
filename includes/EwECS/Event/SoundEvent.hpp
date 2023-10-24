//
// Created by beafowl on 24/10/23.
//

#ifndef EWECS_SOUNDEVENT_HPP
#define EWECS_SOUNDEVENT_HPP

namespace ECS::Event {
    enum class SoundEventType
    {
        PLAY = 0, /*!< The sound is playing. */
        STOP = 1, /*!< The sound is stopped. */
        PAUSE = 2 /*!< The sound is paused. */
    };

    enum class SoundType
    {
        MUSIC = 0, /*!< The sound is a music. */
        SOUND = 1  /*!< The sound is a sound. */
    };

    enum class SoundState
    {
        PLAYING = 0, /*!< The sound is playing. */
        STOPPED = 1, /*!< The sound is stopped. */
        PAUSED = 2   /*!< The sound is paused. */
    };

    /**
     * @brief Sound event class is the base class of all sound events
     *
     */
    class SoundEvent {
        public:
            //-------------------CONSTRUCTORS / DESTRUCTOR-------------------//
            /**
             * @brief Construct a new Sound Event object
             *
             * @param aSoundEventType The type of the sound event.
             */
            explicit SoundEvent(const SoundEventType &aSoundEventType, const SoundType &aSoundType, const SoundState &aSoundState);

            SoundEvent(const SoundEvent &soundEvent) = default;
            SoundEvent(SoundEvent &&soundEvent) = default;
            SoundEvent &operator=(const SoundEvent &soundEvent) = default;
            SoundEvent &operator=(SoundEvent &&soundEvent) noexcept = default;

            //-------------------ATTRIBUTES-------------------//
            SoundEventType _soundEventType; /*!< The type of the sound event. */
            SoundState _soundState;         /*!< The state of the sound. */
            SoundType _soundType;          /*!< The type of the sound. */
    };
}

#endif // EWECS_SOUNDEVENT_HPP
