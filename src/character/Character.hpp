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
        Character();
        ~Character();

    protected:
    private:
        sf::Texture _koala_texture;
        sf::Sprite _koala_picture;
};

#endif /* !CHARACTER_HPP_ */
