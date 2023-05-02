#include "Toolbox.h"
#include "Tile.h"
#include "Button.h"
#include "Gamestate.h"
#include "minesweeper.h"
#include <iostream>
Toolbox& Toolbox::getInstance(){
    static Toolbox toolbox;
    return toolbox;
}
Toolbox::Toolbox(){ //initializes the buttons, gameboard, and any elements necessary to play the game.
// creates our window
    this->window.create(sf::VideoMode(800, 600), "P4 – Minesweeper, Ethan");
    this->window.clear(sf::Color::White);
    this->gamestate = new Gamestate(); //initialize the gamestate to random
this->boardVector = this->gamestate->boardVector;
    //this will handle creating button 1
    auto butt1_pos = sf::Vector2f(550,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        Button* testb1 = new Button(butt1_pos,load_board1);
        this->testButton1 = testb1;
        auto butt1_texture = new sf::Texture;
        butt1_texture->loadFromFile("images/test_1.png");
        auto butt1_sprite = new sf::Sprite(*butt1_texture);
        butt1_sprite->setPosition(550,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        testb1->setSprite(butt1_sprite);
        this->window.draw(*testb1->getSprite());
    //this will handle creating button 2
    auto butt2_pos = sf::Vector2f(550+butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        Button* testb2 = new Button(butt2_pos,load_board2); //set button 2
        this->testButton2 = testb2;
        auto butt2_texture = new sf::Texture;
        butt2_texture->loadFromFile("images/test_2.png");
        auto butt2_sprite = new sf::Sprite(*butt2_texture);
        butt2_sprite->setPosition(550+butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        testb2->setSprite(butt2_sprite);
        this->window.draw(*testb2->getSprite());
    //this will handle creating the debug button
    auto buttd_pos = sf::Vector2f(550-butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        Button* buttd = new Button(buttd_pos,toggleDebugMode); //load debug button
        this->debugButton = buttd;
        auto buttd_texture = new sf::Texture;
        buttd_texture->loadFromFile("images/debug.png");
        auto buttd_sprite = new sf::Sprite(*buttd_texture);
        buttd_sprite->setPosition(550-butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        buttd->setSprite(buttd_sprite);
        this->window.draw(*buttd->getSprite());
    // this will create the new game button
    auto ngb_pos = sf::Vector2f(550-3*butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        Button* ngb = new Button(ngb_pos,restart); //when pressed should call restart
        this->newGameButton = ngb;
        auto ngb_texture = new sf::Texture;
        ngb_texture->loadFromFile("images/face_happy.png");
        auto ngb_sprite = new sf::Sprite(*ngb_texture);
        ngb_sprite->setPosition(550-3*butt1_sprite->getGlobalBounds().width,this->gamestate->get_dimensions().y*this->gamestate->getTile(0,0)->curr_sprite->getGlobalBounds().height);
        ngb->setSprite(ngb_sprite);
        this->window.draw(*ngb->getSprite());
    // now i will load the tile textures
         auto hiddenPointer = new sf::Texture;
            hiddenPointer->loadFromFile("images/tile_hidden.png");
            this->hidden_texture = hiddenPointer;
        auto flagPointer = new sf::Texture;
            flagPointer->loadFromFile("images/flag.png");
            this->flag_texture = flagPointer;
        auto revealedPointer = new sf::Texture;
            revealedPointer->loadFromFile("images/tile_revealed.png");
            this->revealed_texture = revealedPointer;
        auto explodedPointer = new sf::Texture;
            explodedPointer->loadFromFile("images/mine.png");
            this->exploded_texture = explodedPointer;
    //Here we load all the number files
    auto number1 = new sf::Texture;
        number1->loadFromFile("images/number_1.png");
        this->number1_texture = number1;
    auto number2 = new sf::Texture;
        number2->loadFromFile("images/number_2.png");
        this->number2_texture = number2;
    auto number3 = new sf::Texture;
        number3->loadFromFile("images/number_3.png");
        this->number3_texture = number3;
    auto number4 = new sf::Texture;
        number4->loadFromFile("images/number_4.png");
        this->number4_texture = number4;
    auto number5 = new sf::Texture;
        number5->loadFromFile("images/number_5.png");
        this->number5_texture = number5;
    auto number6 = new sf::Texture;
        number6->loadFromFile("images/number_6.png");
        this->number6_texture = number6;
    auto number7 = new sf::Texture;
        number7->loadFromFile("images/number_7.png");
        this->number7_texture = number7;
    auto number8 = new sf::Texture;
        number8->loadFromFile("images/number_8.png");
        this->number8_texture = number8;
//Here we load the win and loss faces
    auto lossFace = new sf::Texture(); //load the loss texture
        lossFace->loadFromFile("images/face_lose.png");
        this->lossTexture = lossFace;
    auto winFace = new sf::Texture(); //load the win texture
        winFace->loadFromFile("images/face_win.png");
        this->winTexture = winFace;
        //here we will load the mine digits
auto digits_texture = new sf::Texture;
digits_texture->loadFromFile("images/digits.png");
this->digits = digits_texture;
this->digit1 = new sf::Sprite(*this->digits);
digit1->setPosition(0,this->newGameButton->getPosition().y);
    this->digit2 = new sf::Sprite(*this->digits);
    digit2->setPosition(21,this->newGameButton->getPosition().y);
    this->digit3 = new sf::Sprite(*this->digits);
    digit3->setPosition(42,this->newGameButton->getPosition().y);
    this->digit1rect = new sf::IntRect;
    this->digit1rect->top = 0;
    this->digit1rect->left = 21*getDigits(this->gamestate->getMineCount())[0];
    this->digit1rect->width = 21; //the width of each digit
    this->digit1rect->height = 32;//the height of each digit
    digit1->setTextureRect(*digit1rect);
    this->digit2rect = new sf::IntRect;
    this->digit2rect->top = 0;
    this->digit2rect->width = 21;
    this->digit2rect->height = 32;
    this->digit2rect->left = 21*getDigits(this->gamestate->getMineCount())[1];
    digit2->setTextureRect(*digit2rect);
    this->digit3rect = new sf::IntRect;
    this->digit3rect->top = 0;
    this->digit3rect->width = 21;
    this->digit3rect->height = 32;
    this->digit3rect->left = 21*getDigits(this->gamestate->getMineCount())[2];
    digit3->setTextureRect(*digit3rect);
    //draw initial digits
    this->window.draw(*this->digit1);
    this->window.draw(*this->digit2);
    this->window.draw(*this->digit3);

}
bool Toolbox::isMine(int x, int y){
    return this->gamestate->getTile(x, y)->is_mine;
}
void Toolbox::setPlayStatus(Gamestate::PlayStatus status){
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.gamestate->setPlayStatus(status);
    if(status==Gamestate::PlayStatus::WIN)
    {
        auto winSprite = new sf::Sprite(*toolbox.winTexture);
        winSprite->setPosition(toolbox.newGameButton->getPosition());
        toolbox.newGameButton->setSprite(winSprite);
    }
    if(status==Gamestate::PlayStatus::LOSS)
    {
        auto lossSprite = new sf::Sprite(*toolbox.lossTexture);
        lossSprite->setPosition(toolbox.newGameButton->getPosition());
        toolbox.newGameButton->setSprite(lossSprite);
    }
}


vector<int> Toolbox::getDigits(int number)
{
    if(number>99)
    {
        int digit1 = (number - number % 100) / 100;
        int digit2 = (number % 100 - number % 10) / 10;
        int digit3 = number % 10;
        vector<int> nums;
        nums.push_back(digit1);
        nums.push_back(digit2);
        nums.push_back(digit3);
        return nums;
    }
    else{
        int digit1 = 0;
        if(number<0)
        {
            digit1 = 10;            //this will grab '-' from digits to make it negative.
            number = number * (-1); //this allows us to operate normally on the negative.
        }
        int digit2 = (number - number % 10) / 10;
        int digit3 = number%10;
        vector<int> nums;
        nums.push_back(digit1);
        nums.push_back(digit2);
        nums.push_back(digit3);
        return nums;
    }
}