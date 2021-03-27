/*
** EPITECH PROJECT, 2021
** main.cpp
** File description:
** main.cpp
*/

#include "main.hpp"

int main(int ac, char *av[])
{
    (void)ac;
    (void)av;
    srand (time(NULL));
    SfmlDrawer windows;
    windows.gameLoop();
    return 0;
}