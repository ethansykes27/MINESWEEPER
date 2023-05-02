#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Gamestate.h"

#include <vector>
using namespace std;
class Toolbox{
    Toolbox();
public:
    sf::RenderWindow window;
    Gamestate* gamestate{};
    Button* debugButton{};
    Button* newGameButton{};
    Button* testButton1{};
    Button* testButton2{};
    vector<int> getDigits(int number);
    static Toolbox& getInstance();
    friend class Tile;
    friend class Gamestate;
    friend class Button;
    vector<bool> boardVector;
    bool isMine(int x, int y); //goes into the gamestate and checks if a tile is a mine
    void setPlayStatus(Gamestate::PlayStatus status);
    sf::Texture* digits; //has all the digits
    sf::Sprite* digit1;     //first mine counter digit
    sf::Sprite* digit2;        //second etc.
    sf::Sprite* digit3;
    sf::IntRect* digit1rect;    //texture rectangle for first digit
    sf::IntRect* digit2rect;    //'' for second etc
    sf::IntRect* digit3rect;
private:
sf::Texture* hidden_texture;    //bunch of textures stored here
sf::Texture* flag_texture;
sf::Texture* revealed_texture;
sf::Texture* exploded_texture;
sf::Texture* number1_texture;
sf::Texture* number2_texture;
sf::Texture* number3_texture;
sf::Texture* number4_texture;
sf::Texture* number5_texture;
sf::Texture* number6_texture;
sf::Texture* number7_texture;
sf::Texture* number8_texture;
sf::Texture* lossTexture;
sf::Texture* winTexture;
};

