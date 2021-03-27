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
        bool checkClick(sf::Vector2i _mousePos, sf::Vector2f _characterPos, sf::Vector2u size, Character &character);
        bool isOpen();
        void drawScoreBoard();
        void handleSpeed();
        void drawLife();
        void looseScreen();
    protected:
    private:
        sf::RenderWindow _window;
        sf::Event _event;
        sf::Font _font;
        sf::Text _score;
        sf::Text _lifeRemaining;
        sf::Text _looseText;
        sf::Texture _mouseTexture;
        sf::Sprite _mouseSprite;
        sf::Texture _heartTexture;
        sf::Sprite _heartSprite;
        double _scoreValue = 0;
        int _life = 6;
        int _speed = 1400;
        bool _isMenue = false;
        bool _isPlaying = true;
        bool _isEnglish = true;
        std::vector<Character *>_character;
};

#endif /* !SFMLDRAWER_HPP_ */
