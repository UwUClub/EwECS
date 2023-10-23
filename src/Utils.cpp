#include "Utils.hpp"

ECS::Utils::Vector2i::Vector2i()
    : x(0),
      y(0)
{}

ECS::Utils::Vector2f::Vector2f()
    : x(0),
      y(0)
{}

ECS::Utils::Vector2i::Vector2i(int aX, int aY)
    : x(aX),
      y(aY)
{}

ECS::Utils::Vector2f::Vector2f(float aX, float aY)
    : x(aX),
      y(aY)
{}
