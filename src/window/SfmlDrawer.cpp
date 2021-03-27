/*
** EPITECH PROJECT, 2021
** SfmlDrawer.cpp
** File description:
** SfmlDrawer.cpp
*/

#include "SfmlDrawer.hpp"
#include "../main.hpp"

SfmlDrawer::SfmlDrawer(): _window(sf::VideoMode(1920, 1080), "GPasVu Jam 2")
{
    static sf::Event event;
    _event = event;
    if (!_font.loadFromFile("assets/OMEGLE.ttf")) {
        std::cerr << "error while loading font" << std::endl;
        return;
    }
    _score.setFont(_font);
    _character = new Character();
    _character->_pos = {500, 500};
    _character->_sprite.setPosition(_character->_pos);
}

SfmlDrawer::~SfmlDrawer()
{
    if (!_character)
        delete(_character);
}

void SfmlDrawer::gameLoop()
{
    while (isOpen())
    {
        clear_screen();
        sf::Time time = _clock.getElapsedTime();
        if (time.asSeconds() > 0.5) {
            _scoreValue++;
            _clock.restart();
        }
        drawScoreBoard();
        _window.draw(_character->_sprite);
    }
}

bool SfmlDrawer::isOpen()
{
    return (_window.isOpen());
}

void SfmlDrawer::drawScoreBoard()
{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(0);
    streamObj << _scoreValue;
    std::string Score = streamObj.str();

    _score.setCharacterSize(20);
    _score.setFillColor(sf::Color::Red);
    _score.setString(Score);
    _score.setPosition(960, 540);
    _window.draw(_score);
}

void SfmlDrawer::handle_keys()
{
    if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Escape)
        _window.close();
}

void SfmlDrawer::clear_screen()
{
    while (_window.pollEvent(_event))
    {
        handle_keys();
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    _window.display();
    _window.clear();
}
