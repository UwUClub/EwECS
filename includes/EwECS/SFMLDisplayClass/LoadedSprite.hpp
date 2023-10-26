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
#include <vector>
#include "EwECS/ConfigReader/ConfigReader.hpp"

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
                  timer(0),
                  currentRect(0),
                  scale(1.0)
            {}

            /**
             * @brief Construct a new Loaded Sprite object
             *
             * @param aPath path to the JSON config file
             */
            LoadedSprite(std::string aJsonPath)
                : 
                  texture(nullptr),
                  timer(0),
                  currentRect(0)
            {
                auto config = ConfigReader::getInstance();
                auto &json = config.loadConfig(aJsonPath);

                path = json["path"];
                scale = json["scale"];
                auto &rects = json["rects"];
                for (auto &frame : rects) {
                    this->rect.emplace_back(frame["top"], frame["left"], frame["width"], frame["height"]);
                    this->rectTime.emplace_back(frame["time"]);
                }
            }
        
            std::string path;
            sf::Texture *texture;
            std::vector<sf::IntRect> rect;
            std::vector<float> rectTime;
            float timer;
            size_t currentRect;
            float scale;
    };
} // namespace Component
#endif // DEBUG