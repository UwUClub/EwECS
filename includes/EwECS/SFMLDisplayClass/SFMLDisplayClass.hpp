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
    #include "EwECS/Event/KeyboardEvent.hpp"
    #include "EwECS/SFMLDisplayClass/LoadedSprite.hpp"
    #include "EwECS/SFMLDisplayClass/TextComponent.hpp"
    #include "EwECS/Utils.hpp"
    #include "EwECS/World.hpp"
    #include "SFML/Graphics/Font.hpp"
    #include "SFML/Graphics/Text.hpp"
    #include <unordered_map>

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
             * @brief Get the player input
             *
             */
            static void getInput();

            /**
             * @brief Display all the entities of the game
             *
             * @param aSprites SparseArray of all the sprites
             * @param aPos SparseArray of all the positions
             */
            static void displayEntities(Core::SparseArray<Component::LoadedSprite> &aSprites,
                                        Core::SparseArray<Utils::Vector2f> &aPos);

            /**
             * @brief Load all the textures of the game
             *
             * @param aSprites SparseArray of all the sprites
             */
            static void loadTextures(Core::SparseArray<Component::LoadedSprite> &aSprites);

            /**
             * @brief Display all the texts of the game
             *
             * @param aTexts SparseArray of all the texts
             */
            static void displayTexts(Core::SparseArray<Component::TextComponent> &aTexts);

            /**
             * @brief call the display function of the window
             *
             */
            static void display();

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
            /**
             * @brief Construct a new SFMLDisplayClass object
             *
             */
            SFMLDisplayClass();
    };

#endif /* !SDLDISPLAYClass_HPP_ */
} // namespace ECS
