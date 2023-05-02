#include "Tile.h"
#include "Toolbox.h"
#include "minesweeper.h"
#include <iostream>
using namespace std;
Tile::Tile(sf::Vector2f position) {
this->_state = HIDDEN; //set initial state to hidden
this->_position = position; // set the location of the tile
    //load the hidden sprite
    auto hidden_texture = new sf::Texture;
    hidden_texture->loadFromFile("images/tile_hidden.png");
    this->hidden_sprite = new sf::Sprite(*hidden_texture);
    this->hidden_sprite->setPosition(position);
    //load the revealed sprite
    auto revealed_texture = new sf::Texture;
    revealed_texture->loadFromFile("images/tile_revealed.png");
    this->revealed_sprite = new sf::Sprite(*revealed_texture);
    this->revealed_sprite->setPosition(position);
    //load the exploded sprite
    auto exploded_texture = new sf::Texture;
    exploded_texture->loadFromFile("images/mine.png");
    this->exploded_sprite = new sf::Sprite(*exploded_texture);
    this->exploded_sprite->setPosition(position);
    //load the flag sprite
    auto flag_texture = new sf::Texture;
    flag_texture->loadFromFile("images/flag.png");
    this->flag_sprite = new sf::Sprite(*flag_texture);
    this->flag_sprite->setPosition(position);
}
sf::Vector2f Tile::getLocation(){
    return this->_position;
}
Tile::State Tile::getState(){
    return _state;
}
void Tile::draw()
{
    Toolbox& toolbox = Toolbox::getInstance();

    if (_state == HIDDEN)
    {
        toolbox.window.draw(*this->hidden_sprite);
        if(this->flagged)
            this->setState(FLAGGED);
    }
    if (_state == FLAGGED)
    {
        this->flagged = true; //set the flagged bool to true

        toolbox.window.draw(*this->hidden_sprite);
        toolbox.window.draw(*this->flag_sprite);

    }
    if (_state == EXPLODED)
    {
        if(getDebugMode())
            toolbox.window.draw(*this->hidden_sprite);
        else
            toolbox.window.draw(*this->revealed_sprite);
        toolbox.window.draw(*this->exploded_sprite);
    }
    if (_state == REVEALED)
    {
        Toolbox& toolbox = Toolbox::getInstance();
        toolbox.window.draw(*this->revealed_sprite);
        toolbox.window.draw(*this->curr_sprite);
    }
}
std::array<Tile*, 8>& Tile::getNeighbors(){
return this->neighborArray;
}
void Tile::setState(State new_state){
    this->_state = new_state;
}
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors){
    Toolbox& toolbox = Toolbox::getInstance(); // initialized the array to nullptr
        auto hiddenSprite = sf::Sprite(*toolbox.hidden_texture);
        auto tileSize =  hiddenSprite.getGlobalBounds(); //get the size of the tiles
        //
        auto tilePos = this->getLocation();
        tilePos.x = tilePos.x / tileSize.width; //this sets the position of the tile in the grid
        tilePos.y = tilePos.y / tileSize.height;
        //now we can use get tile to find all the neighbors
            this->neighborArray[0] = toolbox.gamestate->getTile(tilePos.x-1,tilePos.y-1);
            this->neighborArray[1] = toolbox.gamestate->getTile(tilePos.x,tilePos.y-1);
            this->neighborArray[2] = toolbox.gamestate->getTile(tilePos.x+1,tilePos.y-1);
            this->neighborArray[3] = toolbox.gamestate->getTile(tilePos.x-1,tilePos.y);
            this->neighborArray[4] = toolbox.gamestate->getTile(tilePos.x+1,tilePos.y);
            this->neighborArray[5] = toolbox.gamestate->getTile(tilePos.x-1,tilePos.y+1);
            this->neighborArray[6] = toolbox.gamestate->getTile(tilePos.x,tilePos.y+1);
            this->neighborArray[7] = toolbox.gamestate->getTile(tilePos.x+1,tilePos.y+1);
this->neighbors_set = true;
}
void Tile::onClickLeft(){

    if(this->is_mine) // if its a mine we explode it
    {
        this->setState(EXPLODED);
        if(!getDebugMode()){
            Toolbox& toolbox = Toolbox::getInstance();
        toolbox.setPlayStatus(Gamestate::PlayStatus::LOSS);
        }
    }
    else{//else its a normal revealed tile
    if(!this->neighbors_set)
    {
        this->setNeighbors(this->neighborArray);
    }
    int *mine_count = new int(0);
    for(int i =0; i<8;i++){
        if((this->neighborArray[i] != nullptr)){
            if(this->neighborArray[i]->is_mine)
            {
                auto new_count = *mine_count +1;
                *mine_count = new_count;
            }//end if
        } // end if
    }     // end for

    Toolbox& toolbox = Toolbox::getInstance();

    if(*mine_count==0){
        this->curr_sprite = this->revealed_sprite;
        if((this->getState()==FLAGGED) || (this->getState()==HIDDEN) )
        {
            this->setState(REVEALED); //when its clicked we want to set the state to revealed
        }
       this->revealNeighbors();
    }
        if((this->getState()==FLAGGED) || (this->getState()==HIDDEN) )
        {
            this->setState(REVEALED); //when its clicked we want to set the state to revealed
            resetDigits(); //if it goes from flagged to revealed
        }
    if(*mine_count==1){ //get the correct number sprite now
        sf::Sprite *number1 = new sf::Sprite(*toolbox.number1_texture);
        this->curr_sprite = number1;
    }
    if(*mine_count==2){
        sf::Sprite *number2 = new sf::Sprite(*toolbox.number2_texture);
        this->curr_sprite = number2;
    }
    if(*mine_count==3){
        sf::Sprite *number3 = new sf::Sprite(*toolbox.number3_texture);
        this->curr_sprite = number3;
    }
    if(*mine_count==4){
        sf::Sprite *number4 = new sf::Sprite(*toolbox.number4_texture);
        this->curr_sprite = number4;
    }
    if(*mine_count==5){
        sf::Sprite *number5 = new sf::Sprite(*toolbox.number5_texture);
        this->curr_sprite = number5;
    }
    if(*mine_count==6){
        sf::Sprite *number6 = new sf::Sprite(*toolbox.number6_texture);
        this->curr_sprite = number6;
    }
    if(*mine_count==7){
        sf::Sprite *number7 = new sf::Sprite(*toolbox.number7_texture);
        this->curr_sprite = number7;
    }
    if(*mine_count==8){
        sf::Sprite *number8 = new sf::Sprite(*toolbox.number8_texture);
        this->curr_sprite = number8;
    }
    curr_sprite->setPosition(this->getLocation()); //set the position of the number sprite
} //end else
    }
void Tile::onClickRight() {

    if((this->getState()!=Tile::REVEALED)&&(this->getState()!=Tile::EXPLODED))
    {
        if(this->getState()==FLAGGED)
           this->flagged = false; //make sure to reset the flagged bool if we are taking away a flag
        this->setState((this->getState() == Tile::HIDDEN) ? (Tile::FLAGGED) : (Tile::HIDDEN));
        //now we have to change the mine counter
        resetDigits();
    }//end if
}
void Tile::revealNeighbors() {
    for(auto tile:this->getNeighbors()){
        if((tile != nullptr)&&(tile->getState()!=Tile::REVEALED)){
            tile->onClickLeft();
        }
    }
} // end of reveal neighbors function

Tile::~Tile(){
    delete this->hidden_sprite;
    delete this->revealed_sprite;
    delete this->exploded_sprite;
    delete this->flag_sprite;
}