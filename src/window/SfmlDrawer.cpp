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
    if (!_mouseTexture.loadFromFile("assets/crossair.png")) {
        std::cerr << "error while loading font" << std::endl;
        return;
    }
    sf::Sprite temp(_mouseTexture);
    _mouseSprite = temp;
    sf::Vector2u _size = _mouseTexture.getSize();
    _mouseSprite.setOrigin(_size.x / 2, _size.y / 2);
    _window.setMouseCursorVisible(false);
    _score.setFont(_font);
    _character.push_back(new Character("assets/nyanCatSprite.png", {500, 500}));
    _character.push_back(new Character("assets/Homer.png", {500, 500}));
}

SfmlDrawer::~SfmlDrawer()
{
    for (auto const &it: _character) {
        if (!it)
            delete(it);
    }
}

void SfmlDrawer::updateMouseSpritePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    _mouseSprite.setPosition(mousePos.x, mousePos.y);
    _window.draw(_mouseSprite);
}

void SfmlDrawer::gameLoop()
{
    while (isOpen())
    {
        clear_screen();
        updateCharacterPos();
        for (auto const &it: _character) {
            (it->isAlive == true) ? _window.draw(it->_sprite) : (void)0; // degueulasse
        }
        drawScoreBoard();
        updateMouseSpritePos();
    }
}

void SfmlDrawer::checkClick(sf::Vector2i _mousePos, sf::Vector2f _characterPos, sf::Vector2u size, Character &character)
{
    float posMinX = _characterPos.x - (size.x / 2);
    float posMinY = _characterPos.y - (size.y / 2);
    float posMaxX = _characterPos.x + (size.x / 2);
    float posMaxY = _characterPos.y + (size.y / 2);

    if ((_mousePos.x >= posMinX && _mousePos.x <= posMaxX)
    && (_mousePos.y >= posMinY && _mousePos.y <= posMaxY))
    {
        _scoreValue++;
        character.isAlive = false;
        return;
    }
}

void SfmlDrawer::updateCharacterPos()
{
    for (auto const &it: _character) {
        sf::Time time = it->_clockCharacter.getElapsedTime();
        if (time.asMilliseconds() > 700) {
            float x = rand() % (1920 - (it->_texture.getSize().x) - 50) + (it->_texture.getSize().x / 2);
            float y = rand() % (1080 - (it->_texture.getSize().y) - 50) + (it->_texture.getSize().y / 2);

            it->_pos = {x, y};
            it->_sprite.setPosition(x, y);
            it->reviveCharacter();
            it->_clockCharacter.restart();
        }
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

    _score.setCharacterSize(60);
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
            for (const auto &it: _character) {
                (it->isAlive == true) ? checkClick(mousePos, it->_pos, it->_texture.getSize(), *it) : (void)0;
            }
        }
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    _window.display();
    _window.clear();
}
