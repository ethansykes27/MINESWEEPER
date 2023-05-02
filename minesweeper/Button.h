#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Gamestate.h"
class Button{
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
    friend class Toolbox;
private:
    sf::Vector2f position;
    std::function<void(void)> click_function;
    sf::Sprite* button_sprite;
    Gamestate* board;
};
