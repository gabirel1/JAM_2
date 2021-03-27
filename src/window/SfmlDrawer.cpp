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
        updateCharacterPos();
        drawScoreBoard();
        (_character->isAlive == true) ? _window.draw(_character->_sprite) : (void)0; // degueulasse

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
        _scoreValue++;
        _character->isAlive = false;
        return;
    }
}

void SfmlDrawer::updateCharacterPos()
{
    sf::Time time = _clockCharacter.getElapsedTime();
    if (time.asMilliseconds() > 700) {
        float x = rand() % 500;
        float y = rand() % 500;
        _character->_pos = {x, y};
        _character->_sprite.setPosition(x, y);
        _character->reviveCharacter();
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

    _score.setCharacterSize(40);
    _score.setFillColor(sf::Color::Red);
    _score.setString(Score);

    sf::Vector2u winSize = _window.getSize();
    float sizeX = winSize.x;

    sf::FloatRect textRect = _score.getLocalBounds();
    _score.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    float posX = (sizeX / 2);

    _score.setPosition(posX, 40);
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
            (_character->isAlive == true) ? checkClick(mousePos, _character->_pos, _character->_texture.getSize()) : (void)0;
        }
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    _window.display();
    _window.clear();
}
