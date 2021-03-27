/*
** EPITECH PROJECT, 2021
** Character.cpp
** File description:
** Character.cpp
*/

#include "Character.hpp"

Character::Character()
{
    if (!_texture.loadFromFile("assets/nyanCatSprite.png")) {
        std::cerr << "error while loading picture" << std::endl;
        return;
    }
    sf::Sprite temp(_texture);
    _sprite = temp;
    sf::Vector2u _size = _texture.getSize();
    _sprite.setOrigin(_size.x / 2, _size.y / 2);
    _pos = {-260, -260};
}

Character::~Character()
{
}

void Character::reviveCharacter()
{
    isAlive = true;
}