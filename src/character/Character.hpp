/*
** EPITECH PROJECT, 2021
** Character.hpp
** File description:
** Character.hpp
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "../main.hpp"

class Character {
    public:
        Character(const std::string &_filepath, sf::Vector2f pos);
        ~Character();
        void reviveCharacter();

        bool isAlive = true;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _pos;
        sf::Clock _clockCharacter;
    protected:
    private:
};

#endif /* !CHARACTER_HPP_ */
