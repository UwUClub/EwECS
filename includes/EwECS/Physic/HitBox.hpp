#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <cstddef>
namespace Component {
    struct HitBox
    {
            /**
             * @brief Construct a new Hit Box object
             *
             */
            HitBox()
                : width(0),
                  height(0),
                  isColliding(false),
                  collidingId(0)
            {}
            /**
             * @brief Construct a new Hit Box object
             *
             * @param aWidth Width of the hitbox
             * @param aHeight Height of the hitbox
             */
            HitBox(float aWidth, float aHeight)
                : width(aWidth),
                  height(aHeight),
                  isColliding(false),
                  collidingId(0)
            {}
            float width;
            float height;
            bool isColliding;
            size_t collidingId;
    };
} // namespace Component

#endif /* !HITBOX_HPP_ */