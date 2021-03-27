/*
** EPITECH PROJECT, 2021
** SfmlDrawer.hpp
** File description:
** SfmlDrawer.hpp
*/

#ifndef SFMLDRAWER_HPP_
#define SFMLDRAWER_HPP_

#include "../main.hpp"
#include "../character/Character.hpp"

class Character;
class SfmlDrawer {
    public:
        SfmlDrawer();
        ~SfmlDrawer();

        void gameLoop();
        void clear_screen();
        void handle_keys();
        void updateCharacterPos();
        void updateMouseSpritePos();
        void checkClick(sf::Vector2i _mousePos, sf::Vector2f _characterPos, sf::Vector2u size, Character &character);
        bool isOpen();
        void drawScoreBoard();
    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        sf::Text _score;
        sf::Texture _mouseTexture;
        sf::Sprite _mouseSprite;
        double _scoreValue = 0;
        // Character *_character;
        std::vector<Character *>_character;
};

#endif /* !SFMLDRAWER_HPP_ */
