#ifndef UTILS_HPP
#define UTILS_HPP

namespace ECS::Utils {
    struct Vector2i
    {
            Vector2i();

            Vector2i(int aX, int aY);

            int x;
            int y;
    };

    struct Vector2f
    {
            Vector2f();

            Vector2f(float aX, float aY);

            float x;
            float y;
    };
} // namespace ECS::Utils

#endif // !
