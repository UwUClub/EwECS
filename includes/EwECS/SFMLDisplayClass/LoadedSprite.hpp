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

#ifndef LOADEDSPRITE_HPP
    #define LOADEDSPRITE_HPP

namespace Component {
    struct LoadedSprite
    {
            /**
             * @brief Construct a new Loaded Sprite object
             *
             */
            LoadedSprite()
                : texture(nullptr),
                  rect(sf::IntRect(0, 0, 0, 0))
            {}
            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the sprite
             * @param aTexture texture of the sprite (once loaded)
             * @param aLeft left position of the sprite in the texture
             * @param aTop top position of the sprite in the texture
             * @param aWidth width of the sprite in the texture
             * @param aHeight height of the sprite in the texture
             */
            LoadedSprite(std::string aPath, sf::Texture *aTexture, int aLeft, int aTop, int aWidth, int aHeight)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(sf::IntRect{aLeft, aTop, aWidth, aHeight})
            {}

            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the sprite
             * @param aTexture texture of the sprite (once loaded)
             * @param aLeft left position of the sprite in the texture
             * @param aTop top position of the sprite in the texture
             * @param aWidth width of the sprite in the texture
             * @param aHeight height of the sprite in the texture
             * @param aScale scale of the sprite
             */
            LoadedSprite(std::string aPath, sf::Texture *aTexture, int aLeft, int aTop, int aWidth, int aHeight, float aScale)
                : path(std::move(aPath)),
                  texture(aTexture),
                  rect(sf::IntRect{aLeft, aTop, aWidth, aHeight}),
                  scale(aScale)
            {}

            std::string path;
            sf::Texture *texture;
            sf::IntRect rect;
            float scale = 1.0;
    };
} // namespace Component
#endif // DEBUG