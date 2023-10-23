/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SFMLDisplayClass
*/

#ifndef SDLDISPLAYClass_HPP_
#define SDLDISPLAYClass_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>
#include <cstddef>
#include <string>
#include <unordered_map>
#include "LoadedSprite.hpp"
#include "KeyboardEvent.hpp"
#include "Utils.hpp"
#include "World.hpp"


namespace ECS {
    class SFMLDisplayClass
    {
        public:
            /**
            * @brief Destroy the SFMLDisplayClass object
            *
            */
            ~SFMLDisplayClass();

            /**
            * @brief Get an Instance of the SFMLDisplayClass (singleton)
            *
            * @return SFMLDisplayClass&
            */
            static SFMLDisplayClass &getInstance()
            {
                static SFMLDisplayClass instance;

                return instance;
            }

            /**
            * @brief Get the texture object
            *
            * @return sf::Texture*
            */
            sf::Texture *getTexture(const std::string &path);

            /**
            * @brief Free the rects of the entity
            *
            * @param idx The index of the entity
            */
            void freeRects(const std::size_t &idx);

            /**
            * @brief Get the player input
            * 
            */
            void getInput();

            void displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                 Core::SparseArray<Utils::Vector2f> &aPos);

            sf::RenderWindow _window;
            std::string _assetPath;

        private:
            /**
             * @brief Map of all the SDL_Keycode and their equivalent in our ECS
             *
             */
            static const inline std::unordered_map<sf::Keyboard::Key, const ECS::Event::KeyIdentifier> _keyMap = {
                {sf::Keyboard::Key::Escape, ECS::Event::KeyIdentifier::ESCAPE},
                {sf::Keyboard::Key::Up, ECS::Event::KeyIdentifier::UP},
                {sf::Keyboard::Key::Down, ECS::Event::KeyIdentifier::DOWN},
                {sf::Keyboard::Key::Left, ECS::Event::KeyIdentifier::LEFT},
                {sf::Keyboard::Key::Right, ECS::Event::KeyIdentifier::RIGHT},
                {sf::Keyboard::Key::Space, ECS::Event::KeyIdentifier::SPACE},
            };

            std::unordered_map<std::string, sf::Texture *> _textures;
            /**
            * @brief Construct a new SFMLDisplayClass object
            *
            */
            SFMLDisplayClass();
    };

    #endif /* !SDLDISPLAYClass_HPP_ */
} // namespace ECS
