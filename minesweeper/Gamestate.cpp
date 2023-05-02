#include "Gamestate.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
#include "Tile.h"
#include <random>
#include "Toolbox.h"
sf::Vector2i Gamestate::get_dimensions(){
    return this->_dimensions;
}
Gamestate::Gamestate(sf::Vector2i _dimensions, int _numberOfMines){ //RNG gamestate
this->_dimensions = _dimensions;
this->numberOfMines = _numberOfMines;
this->setPlayStatus(PLAYING); //set initial play status to playing
int mine_count = 0;
    int boardArray[_dimensions.x][_dimensions.y];
    for(int i= 0 ;i<_dimensions.x;i++){ //this just initializes the array
        for(int j=0;j<_dimensions.y;j++)
            boardArray[i][j] = false;
    } // end for
    std::random_device rd;  //RNG device
    std::mt19937 gen(rd()); //random seed
    std::uniform_int_distribution<> randX(0, _dimensions.x-1);
    std::uniform_int_distribution<> randY(0, _dimensions.y-1);
while(mine_count<_numberOfMines){  //here we populate the array with mines
    int X = randX(gen);
    int Y = randY(gen);
    while(boardArray[X][Y]!= true){
        boardArray[X][Y] = true;
        mine_count++;
    } //end inner while
} //end outer while

    //here we load the hidden texture for all of the tiles
    auto hidden_text = new sf::Texture;
    hidden_text->loadFromFile("images/tile_hidden.png");
    // here we create a dummy sprite to get the size
    sf::Sprite hidden_sprite = sf::Sprite(*hidden_text);
    auto tile_size = hidden_sprite.getGlobalBounds();
    for (int i = 0; i < this->get_dimensions().y; i++)
    {
        for (int j = 0; j < this->get_dimensions().x; j++) //here we initialize the tiles
        {
            sf::Vector2f pos;
            pos.x = j * tile_size.width;
            pos.y = i * tile_size.height;
            Tile* next_tile = new Tile(pos);
            sf::Sprite* hiddenSprite = new sf::Sprite(*hidden_text);

            next_tile->curr_sprite = hiddenSprite;
            next_tile->curr_sprite->setPosition(pos);
            next_tile->is_mine = boardArray[j][i];
            this->boardVector.push_back(boardArray[j][i]);
            this->tile_list.push_back(next_tile);
        } //end inner loop
    }       //end outer loop

}// end of constructor
Gamestate::Gamestate(const char* filepath)
{ //filestream gamestate
    this->setPlayStatus(PLAYING);
    this->_dimensions.x = 25; //set the dimensions
    this->_dimensions.y = 0;
    this->numberOfMines = 0;
    ifstream board_file(filepath);
    bool board_vector[16][25]; // this is a vector of is_mine bool
    int l = 0;
    while(!board_file.eof()&& l<16) // outer loop iterates through each line
    {
        string board_line;
        getline(board_file, board_line);
        this->_dimensions.x = board_line.size();
        for (int j = 0; j < board_line.size(); j++) //this goes through the line and adds the bool
        {
            if(board_line[j]=='1')
            {
                board_vector[l][j] = true;
                this->numberOfMines++;
            }
            if(board_line[j]=='0')
                board_vector[l][j]= false;
        }
        l++;
        this->_dimensions.y = this->get_dimensions().y+1;
    }
    //here we load the hidden texture for all of the tiles
    auto hidden_text = new sf::Texture;
    hidden_text->loadFromFile("images/tile_hidden.png");
    // here we create a dummy sprite to get the size
    sf::Sprite hidden_sprite = sf::Sprite(*hidden_text);
    auto tile_size = hidden_sprite.getGlobalBounds();
    for (int i = 0; i < this->get_dimensions().y; i++)
    {
        for (int j = 0; j < this->get_dimensions().x; j++)
        {
            sf::Vector2f pos;
            pos.x = j * tile_size.width;
            pos.y = i * tile_size.height;
            Tile* next_tile = new Tile(pos);
            sf::Sprite* hiddenSprite = new sf::Sprite(*hidden_text);

            next_tile->curr_sprite = hiddenSprite;
            next_tile->curr_sprite->setPosition(pos);
            next_tile->is_mine = board_vector[i][j];
            this->boardVector.push_back(board_vector[i][j]); //this stores the board in the gamestate
            this->tile_list.push_back(next_tile);
        } //end inner loop
    }       //end outer loop

}//end of constructor

Tile* Gamestate::getTile(int x, int y){
    if(x>=(this->get_dimensions().x)||(x<0)||(y<0)||(y>=this->get_dimensions().y))
        return nullptr;
    return (tile_list)[(y*_dimensions.x+x)];
}
int Gamestate::getMineCount(){
    return this->numberOfMines-this->getFlagCount();//the number of mines - the number of flags placed
}
int Gamestate::getFlagCount(){
    int flagCount = 0;
    for(auto tile:this->tile_list){
        if(tile->getState()==Tile::FLAGGED)
            flagCount++;
    } //end for
    return flagCount;
}     //end function

Gamestate::PlayStatus Gamestate::getPlayStatus() {
    return this->play_status;
}
void Gamestate::setPlayStatus(PlayStatus _status){

    this->play_status = _status;

}
Gamestate::~Gamestate(){
    for(auto tile:this->tile_list)
        delete tile;

}

