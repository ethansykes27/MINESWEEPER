#include "Button.h"
#include <SFML/Graphics.hpp>
#include <functional>

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick){
    this->position = _position;
    this->click_function = _onClick;
}
void Button::onClick(){
click_function();
}
sf::Sprite* Button::getSprite(){
    return button_sprite;
}
void Button::setSprite(sf::Sprite* _sprite){
    this->button_sprite = _sprite;
}
sf::Vector2f  Button::getPosition() {
    return this->position;
}