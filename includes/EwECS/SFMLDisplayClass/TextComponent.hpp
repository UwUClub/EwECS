/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** LoadedSprite
*/

#include <cstddef>
#include <string>
#include <utility>

#ifndef TEXTCOMPONENT_HPP
    #define TEXTCOMPONENT_HPP

namespace Component {
    enum class TextColor
    {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        WHITE,
        BLACK,
        MAGENTA,
        CYAN,
        DEFAULT
    };
    struct TextComponent
    {
            /**
             * @brief Construct a new Loaded Sprite object
             *
             */
            TextComponent() = default;

            /**
             * @brief Construct a new Text object
             *
             * @param text The text to display
             * @param color The color of the text
             * @param size The size of the text
             */
            TextComponent(const std::string &aText, TextColor aColor, std::size_t aSize)
                : text(aText),
                  color(aColor),
                  size(aSize)
            {}

            std::string text;
            TextColor color {};
            std::size_t size {};
    };
} // namespace Component
#endif // DEBUG
