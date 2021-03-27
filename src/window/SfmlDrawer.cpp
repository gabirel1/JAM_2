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
        updateCharacterPos();
        drawScoreBoard();
        _window.draw(_character->_sprite);
    }
}

void SfmlDrawer::checkClick(sf::Vector2i _mousePos, sf::Vector2f _characterPos, sf::Vector2u size)
{
    float posMinX = _characterPos.x - (size.x / 2);
    float posMinY = _characterPos.y - (size.y / 2);
    float posMaxX = _characterPos.x + (size.x / 2);
    float posMaxY = _characterPos.y + (size.y / 2);

    if ((_mousePos.x >= posMinX && _mousePos.x <= posMaxX)
    && (_mousePos.y >= posMinY && _mousePos.y <= posMaxY))
    {
        std::cout << "mouse : " << _mousePos.x << " " << _mousePos.y << " | " << posMinX << " && " << posMaxX << " touched" << std::endl;
        return;
    }
    std::cout << "mouse : " << _mousePos.x << " " << _mousePos.y << " | " << posMinX << " && " << posMaxX << " not touched" << std::endl;
}

void SfmlDrawer::updateCharacterPos()
{
    sf::Time time = _clockCharacter.getElapsedTime();
    if (time.asMilliseconds() > 700) {
        float x = rand() % 500;
        float y = rand() % 500;
        _character->_pos = {x, y};
        _character->_sprite.setPosition(x, y);
        _clockCharacter.restart();
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            checkClick(mousePos, _character->_pos, _character->_texture.getSize());
        }
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    _window.display();
    _window.clear();
}
