/*
** EPITECH PROJECT, 2021
** Character.cpp
** File description:
** Character.cpp
*/

#include "Character.hpp"

Character::Character(const std::string &_filepath, sf::Vector2f pos)
{
    if (!_texture.loadFromFile(_filepath)) {
        std::cerr << "error while loading picture" << std::endl;
        return;
    }
    sf::Sprite temp(_texture);
    _sprite = temp;
    sf::Vector2u _size = _texture.getSize();
    _sprite.setOrigin(_size.x / 2, _size.y / 2);
    _pos = pos;
    _sprite.setPosition(pos);
}

Character::~Character()
{
}

void Character::reviveCharacter()
{
    isAlive = true;
}