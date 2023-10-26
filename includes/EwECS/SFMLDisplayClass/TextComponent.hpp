/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadedSprite
*/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstddef>
#include <string>
#include <utility>
#include "SFML/Graphics/Text.hpp"

#ifndef TEXTCOMPONENT_HPP
    #define TEXTCOMPONENT_HPP

namespace Component {
    struct TextComponent
    {
            /**
             * @brief Construct a new Loaded Sprite object
             *
             */
            TextComponent() = default;

            sf::Text text;
    };
} // namespace Component
#endif // DEBUG
