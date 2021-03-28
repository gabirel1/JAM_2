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
    if (!_heartTexture.loadFromFile("assets/heart.png")) {
        std::cerr << "error while loading font" << std::endl;
        return;
    }
    if (!_frenchTexture.loadFromFile("assets/frenchFlag.jpg")) {
        std::cerr << "error while loading font" << std::endl;
        return;
    }
    if (!_americanTexture.loadFromFile("assets/americanFlag.png")) {
        std::cerr << "error while loading font" << std::endl;
        return;
    }

    sf::Sprite temp(_mouseTexture);
    _mouseSprite = temp;
    sf::Vector2u _size = _mouseTexture.getSize();
    _mouseSprite.setOrigin(_size.x / 2, _size.y / 2);
    _window.setMouseCursorVisible(false);

    sf::Sprite tmp(_heartTexture);
    _heartSprite = tmp;
    sf::Vector2u _size2 = _heartTexture.getSize();
    _heartSprite.setOrigin(_size2.x / 2, _size2.y / 2);

    sf::Sprite tmp1(_frenchTexture);
    sf::Sprite tmp2(_americanTexture);
    _frenchSprite = tmp1;
    _americanSprite = tmp2;

    sf::Vector2u _size3 = _frenchTexture.getSize();
    _frenchSprite.setOrigin(_size3.x / 2, _size3.y / 2);

    sf::Vector2u _size4 = _americanTexture.getSize();
    _americanSprite.setOrigin(_size4.x / 2, _size4.y / 2);

    _score.setFont(_font);
    _lifeRemaining.setFont(_font);
    _looseText.setFont(_font);
    _looseText2.setFont(_font);
    _menuText.setFont(_font);
    _menuText2.setFont(_font);
    _adviceText.setFont(_font);

    _character.push_back(new Character("assets/nyanCatSprite.png", {500, 500}));
    _character.push_back(new Character("assets/Homer.png", {500, 500}));
    _character.push_back(new Character("assets/futurama.png", {500, 500}));

    _americanAdvices.push_back("\"Do what you love. Everything else is secondary\"");
    _frenchAdvices.push_back("\"Fais ce que tu aimes. Tout le reste est secondaire\"");
    _americanAdvices.push_back("\"Don't believe everything you hear\"");
    _frenchAdvices.push_back("\"ne crois pas tout ce que tu entends\"");
}

SfmlDrawer::~SfmlDrawer()
{
    for (auto const &it: _character) {
        if (!it)
            delete(it);
    }
}

void SfmlDrawer::displayMenu()
{
    _frenchSprite.setPosition(1800, 950);
    _americanSprite.setPosition(1600, 950);

    _window.draw(_frenchSprite);
    _window.draw(_americanSprite);

    std::string toPrint = (_isEnglish == true) ? ("Welcome to GpasVu the game !") : ("Bienvenue sur GpasVu le jeu !");
    std::string toPrint2 = (_isEnglish == true) ? ("Press ENTER to start") : ("Appuyez sur ENTREE pour commencer");
    _menuText.setCharacterSize(60);
    _menuText.setFillColor(sf::Color::Red);
    _menuText.setString(toPrint);
    sf::FloatRect textRect = _menuText.getLocalBounds();
    _menuText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    sf::Vector2u winSize = _window.getSize();
    float sizeX = winSize.x;
    float sizeY = winSize.y;
    _menuText.setPosition(sizeX / 2, sizeY / 2);

    _menuText2.setCharacterSize(60);
    _menuText2.setFillColor(sf::Color::Red);
    _menuText2.setString(toPrint2);
    sf::FloatRect textRect2 = _menuText2.getLocalBounds();
    _menuText2.setOrigin(textRect2.left + (textRect2.width / 2.0f), textRect2.top + (textRect2.height / 2.0f));

    _menuText2.setPosition(sizeX / 2, (sizeY / 2) + 200);

    sf::Time time = _clock.getElapsedTime();
    if (time.asMilliseconds() < 1000 && time.asMilliseconds() > 500) {
        _window.draw(_menuText2);
    } else if (time.asMilliseconds() > 1000) {
        _clock.restart();
    }


    _window.draw(_menuText);
}

void SfmlDrawer::updateMouseSpritePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    _mouseSprite.setPosition(mousePos.x, mousePos.y);
    _window.draw(_mouseSprite);
}

void SfmlDrawer::handleSpeed()
{
    static double tmp = _scoreValue;
    if (tmp != _scoreValue && std::fmod(_scoreValue, 10) == 0.0 && _speed > 0) {
        _speed -= 200;
        tmp = _scoreValue;
    }
}

void SfmlDrawer::looseScreen()
{
    static int index = 0;
    if (_wasAlreadyRand == false) {
        index = rand() % _frenchAdvices.size();
    }
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(0);
    streamObj << _scoreValue;
    std::string Score = streamObj.str();

    std::string toPrint = (_isEnglish == true) ? ("\t\tYou Lost.\nWith a score of : " + Score) : ("\tVous avez perdu.\nAvec un score de : " + Score);

    std::string toPrint2 = (_isEnglish == true) ? ("Press R to restart the game") : ("Appuyez sur R pour relancer la partie");

    _looseText.setCharacterSize(160);
    _looseText.setFillColor(sf::Color::Red);
    _looseText.setString(toPrint);
    sf::FloatRect textRect = _looseText.getLocalBounds();
    _looseText.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    _looseText2.setCharacterSize(60);
    _looseText2.setFillColor(sf::Color::Red);
    _looseText2.setString(toPrint2);
    sf::FloatRect textRect2 = _looseText2.getLocalBounds();
    _looseText2.setOrigin(textRect2.left + (textRect2.width / 2.0f), textRect2.top + (textRect2.height / 2.0f));


    sf::Vector2u winSize = _window.getSize();
    float sizeX = winSize.x;
    float sizeY = winSize.y;
    _looseText.setPosition(sizeX / 2, sizeY / 2);
    _looseText2.setPosition(sizeX / 2, ((sizeY / 1.3)));

    _window.draw(_looseText);

    sf::Time time = _clock.getElapsedTime();
    if (time.asMilliseconds() < 1000 && time.asMilliseconds() > 500) {
        _window.draw(_looseText2);
    } else if (time.asMilliseconds() > 1000) {
        _clock.restart();
    }

    _adviceText.setCharacterSize(60);
    _adviceText.setFillColor(sf::Color::Red);
    _adviceText.setString((_isEnglish == true) ? _americanAdvices[index] : _frenchAdvices[index]);
    sf::FloatRect textRect3 = _adviceText.getLocalBounds();
    _adviceText.setOrigin(textRect3.left + (textRect3.width / 2.0f), textRect3.top + (textRect3.height / 2.0f));
    _adviceText.setPosition(sizeX / 2, ((sizeY / 1.15)));
    _window.draw(_adviceText);

    _wasAlreadyRand = true;
}

void SfmlDrawer::gameLoop()
{
    while (isOpen())
    {
        clear_screen();
        if (_isMenu == true) {
            displayMenu();
        } else {
            if (_isPlaying == true) {
                updateCharacterPos();
                for (auto const &it: _character) {
                    (it->isAlive == true) ? _window.draw(it->_sprite) : (void)0; // degueulasse
                }
                handleSpeed();
            } else {
                looseScreen();
            }
            drawScoreBoard();
            drawLife();
        }
        updateMouseSpritePos();
    }
}

bool SfmlDrawer::checkClickMenu(sf::Vector2i _mousePos, sf::Vector2f pos, sf::Vector2u size)
{
    float posMinX = pos.x - (size.x / 2);
    float posMinY = pos.y - (size.y / 2);
    float posMaxX = pos.x + (size.x / 2);
    float posMaxY = pos.y + (size.y / 2);
    if ((_mousePos.x >= posMinX && _mousePos.x <= posMaxX)
    && (_mousePos.y >= posMinY && _mousePos.y <= posMaxY))
    {
        return true;
    }
    return false;
}

bool SfmlDrawer::checkClick(sf::Vector2i _mousePos, sf::Vector2f _characterPos, sf::Vector2u size, Character &character)
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
        return true;
    }
    return false;
}

void SfmlDrawer::updateCharacterPos()
{
    for (auto const &it: _character) {
        sf::Time time = it->_clockCharacter.getElapsedTime();
        if (time.asMilliseconds() > _speed) {
            float x = rand() % (1920 - (it->_texture.getSize().x) - 100) + ((it->_texture.getSize().x / 2) + 50);
            float y = rand() % (1080 - (it->_texture.getSize().y) - 100) + ((it->_texture.getSize().y / 2) + 50);

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

void SfmlDrawer::drawLife()
{
    std::ostringstream streamObj;
    streamObj << _life;
    std::string life = streamObj.str();

    _lifeRemaining.setCharacterSize(60);
    _lifeRemaining.setFillColor(sf::Color::White);
    _lifeRemaining.setString(life);
    sf::FloatRect textRect = _lifeRemaining.getLocalBounds();
    _lifeRemaining.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    _lifeRemaining.setPosition(90, 55);

    _heartSprite.setPosition(200, 60);
    _window.draw(_lifeRemaining);
    _window.draw(_heartSprite);

    if (_life <= 0) {
        _isPlaying = false;
    }
}

void SfmlDrawer::drawScoreBoard()
{
    std::ostringstream streamObj;
    streamObj << std::fixed;
    streamObj << std::setprecision(0);
    streamObj << _scoreValue;
    std::string Score = streamObj.str();

    _score.setCharacterSize(60);
    _score.setFillColor(sf::Color::White);
    _score.setString(Score);

    sf::Vector2u winSize = _window.getSize();
    float sizeX = winSize.x;

    sf::FloatRect textRect = _score.getLocalBounds();
    _score.setOrigin(textRect.left + (textRect.width / 2.0f), textRect.top + (textRect.height / 2.0f));

    float posX = (sizeX / 2);

    _score.setPosition(posX, 55);
    _window.draw(_score);
}

void SfmlDrawer::handle_keys()
{
    if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Escape)
        _window.close();
    if (_isMenu == true && _event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Enter) {
        _isMenu = false;
    }
    if (_isMenu == false && _isPlaying == false && _event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::R) {
        _life = 6;
        _speed = 1400;
        _scoreValue = 0.0;
        _isPlaying = true;
        _wasAlreadyRand = false;
    }
}

void SfmlDrawer::clear_screen()
{
    bool wasTouched = false;

    while (_window.pollEvent(_event))
    {
        handle_keys();
        if (_event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            if (_isPlaying == true && _isMenu == false) {
                for (const auto &it: _character) {
                    if (checkClick(mousePos, it->_pos, it->_texture.getSize(), *it) == true) {
                        wasTouched = true;
                        break;
                    }
                }
                if (wasTouched == false) {
                    _life--;
                }
            } else if (_isMenu == true) {
                if (checkClickMenu(mousePos, _frenchSprite.getPosition(), _frenchTexture.getSize()) == true) {
                    _isEnglish = false;
                } else if (checkClickMenu(mousePos, _americanSprite.getPosition(), _americanTexture.getSize()) == true) {
                    _isEnglish = true;
                }
            }
        }
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
    _window.display();
    _window.clear();
}
