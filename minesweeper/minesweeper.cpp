#include <iostream>
#include <SFML/Graphics.hpp>
#include "Toolbox.h"
#include "minesweeper.h"
int launch(){
    Toolbox& toolbox = Toolbox::getInstance();

    for(int i=0;i<(toolbox.gamestate->get_dimensions().x);i++)
    {
        for (int j = 0; j < (toolbox.gamestate->get_dimensions().y); j++)
        {
//draws the initial board
            toolbox.gamestate->getTile(i, j)->draw();
        }
    }
    toolbox.window.display();
    while (toolbox.window.isOpen())
    {
        sf::Event event;

        while (toolbox.window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                toolbox.window.close(); //close window if u pres on the little x

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    if(event.mouseButton.button==sf::Mouse::Right) //right click registered
                    {
                    int x = sf::Mouse::getPosition(toolbox.window).x;
                    int y = sf::Mouse::getPosition(toolbox.window).y;
                    sf::Texture tilet;
                    tilet.loadFromFile("images/tile_hidden.png");
                    auto tiles = sf::Sprite(tilet);
                    auto tileSize = tiles.getGlobalBounds();

                    for (int i = 0; i < toolbox.gamestate->get_dimensions().x; i++)
                    {
                        for (int j = 0; j < toolbox.gamestate->get_dimensions().y; j++)
                        { //find the tile that the mouse was over when right clicking
                            auto tile = toolbox.gamestate->getTile(i, j);
                            int tile_max_x = tileSize.width + tile->getLocation().x;
                            int tile_max_y = tileSize.height + tile->getLocation().y;
                            if ((tile->getLocation().x < x) && (x < tile_max_x) &&
                                (tile->getLocation().y < y) && (y < tile_max_y))
                            {
                                tile->onClickRight(); //activate the right click behavior for that tile
                                render();
                                toolbox.window.display();
                            }
                        }//inner for
                    }//outer for

                } //end if mouse release
            }//end if mouse press
// Here we will account for left click in a similar way
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    int x = sf::Mouse::getPosition(toolbox.window).x;
                    int y = sf::Mouse::getPosition(toolbox.window).y;
                    //Here we handle if the click was on a tile
                    sf::Texture tilet;
                    tilet.loadFromFile("images/tile_hidden.png");
                    auto tiles = sf::Sprite(tilet);
                    auto tileSize = tiles.getGlobalBounds(); // dummy tile to get size
                    for (int i = 0; i < toolbox.gamestate->get_dimensions().x; i++)
                    {//iterate through the tiles
                        for (int j = 0; j < toolbox.gamestate->get_dimensions().y; j++)
                        {
                            auto tile = toolbox.gamestate->getTile(i, j);
                            int tile_max_x = tileSize.width + tile->getLocation().x;
                            int tile_max_y = tileSize.height + tile->getLocation().y;
                            if ((tile->getLocation().x < x) && (x < tile_max_x) &&
                                (tile->getLocation().y < y) && (y < tile_max_y))
                            {
                                if(toolbox.gamestate->getPlayStatus()==Gamestate::PlayStatus::PLAYING)
                                {// if game is won or lost no behavior should occur
                                    tile->onClickLeft();
                                    gameLoop();

                                    render();
                                    toolbox.window.display();
                                }
                            }
                        }//inner for
                    }//outer for
//Here we will account for if a button is pressed -first get the size of the buttons
                    auto button1Size= toolbox.testButton1->getSprite()->getGlobalBounds();
                    auto button2Size= toolbox.testButton2->getSprite()->getGlobalBounds();
                    auto debugSize= toolbox.debugButton->getSprite()->getGlobalBounds();
                    auto ngbSize = toolbox.newGameButton->getSprite()->getGlobalBounds();
                    if((x>toolbox.testButton1->getPosition().x)&&(x<(toolbox.testButton1->getPosition().x+button1Size.width))&&(y>toolbox.testButton1->getPosition().y)&&(y<(toolbox.testButton1->getPosition().y+button1Size.height)))
                        toolbox.testButton1->onClick();
                    if((x>toolbox.testButton2->getPosition().x)&&(x<(toolbox.testButton2->getPosition().x+button2Size.width))&&(y>toolbox.testButton2->getPosition().y)&&(y<(toolbox.testButton2->getPosition().y+button2Size.height)))
                        toolbox.testButton2->onClick();
                    if((x>toolbox.newGameButton->getPosition().x)&&(x<(toolbox.newGameButton->getPosition().x+ngbSize.width))&&(y>toolbox.newGameButton->getPosition().y)&&(y<(toolbox.newGameButton->getPosition().y+ngbSize.height)))
                        toolbox.newGameButton->onClick();
                    if((x>toolbox.debugButton->getPosition().x)&&(x<(toolbox.debugButton->getPosition().x+debugSize.width))&&(y>toolbox.debugButton->getPosition().y)&&(y<(toolbox.debugButton->getPosition().y+debugSize.height)))
                        toolbox.debugButton->onClick();

                    render();
                    toolbox.window.display();
                    //here we can check if won/lost
                    gameLoop();

                } //end if mouse release left
            }//end if mouse press left
        }//end event poll

    }
return 0;
}

void render(){ //this draws all of the tiles/buttons to the window in their current state
    Toolbox& toolbox = Toolbox::getInstance();
    toolbox.window.clear(sf::Color::White);
    for(int i=0;i<(toolbox.gamestate->get_dimensions().x);i++)
    {
        for (int j = 0; j < (toolbox.gamestate->get_dimensions().y); j++)
        {

            toolbox.gamestate->getTile(i, j)->draw();
        }
    }
    toolbox.window.draw(*toolbox.newGameButton->getSprite());
    toolbox.window.draw(*toolbox.testButton1->getSprite());
    toolbox.window.draw(*toolbox.testButton2->getSprite());
    toolbox.window.draw(*toolbox.debugButton->getSprite());
    //last we draw the mine digits
    toolbox.window.draw(*toolbox.digit1);
    toolbox.window.draw(*toolbox.digit2);
    toolbox.window.draw(*toolbox.digit3);
}
bool debug_mode_on = false;
void toggleDebugMode(){

Toolbox& toolbox = Toolbox::getInstance();
if(!debug_mode_on)
{

    for (int i = 0; i < toolbox.gamestate->get_dimensions().x; i++)
    {
        for (int j = 0; j < toolbox.gamestate->get_dimensions().y; j++)
        {

            auto tile = toolbox.gamestate->getTile(i, j);
            if(toolbox.isMine(i,j)) //invoke the is mine function we created to check if its a mine
                tile->setState(Tile::EXPLODED);
        }
    } //end out for
}//end if
if(debug_mode_on)
{
    for (int i = 0; i < toolbox.gamestate->get_dimensions().x; i++)
    {
        for (int j = 0; j < toolbox.gamestate->get_dimensions().y; j++)
        {
            auto tile = toolbox.gamestate->getTile(i, j);
            if(tile->getState()==Tile::EXPLODED)
                tile->setState(Tile::HIDDEN);

        }
    }//end for

    render();
    resetDigits();
    render();
    toolbox.window.display();
}//end if
    debug_mode_on = !debug_mode_on;
} //end funct
bool getDebugMode(){
    if(debug_mode_on)
        return true;
    return false;
}
int gameLoop(){ //this will check if the game is won
Toolbox& toolbox = Toolbox::getInstance();
if(toolbox.gamestate->getPlayStatus()==Gamestate::PlayStatus::LOSS)
    return 0;
auto status = Gamestate::PlayStatus::WIN;
    for(int i=0;i<toolbox.gamestate->get_dimensions().x;i++){ // this will check for a win
        for(int j=0;j<toolbox.gamestate->get_dimensions().y;j++){
            auto tile = toolbox.gamestate->getTile(i,j);
            if((tile->getState()==Tile::HIDDEN)&&(!toolbox.isMine(i,j)))
            {// if all non mines are revealed

                status = Gamestate::PlayStatus::PLAYING;
                  //we can set playStatus to a win
            }
            }}
    toolbox.setPlayStatus(status);
    return 0;
}
int main()

{ return launch();}

void restart(){ //restarts game with a new RNG board
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gamestate;
    toolbox.gamestate = new Gamestate();
    //reset the new game button
    auto ngb_texture = new sf::Texture;
    ngb_texture->loadFromFile("images/face_happy.png");
    auto ngb_sprite = new sf::Sprite(*ngb_texture);
    ngb_sprite->setPosition(toolbox.newGameButton->getPosition());
    toolbox.newGameButton->setSprite(ngb_sprite);
    toolbox.window.draw(*toolbox.newGameButton->getSprite());
    //Here we reset the mines
    resetDigits();
}


void resetDigits(){ //this sets the digits to the initial mine count of the board
    Toolbox& toolbox = Toolbox::getInstance();
    auto mineCount = toolbox.getDigits(toolbox.gamestate->getMineCount());

    toolbox.digit1rect->left = mineCount[0]*21;
    toolbox.digit1->setTextureRect(*toolbox.digit1rect);
    toolbox.digit2rect->left = mineCount[1]*21;
    toolbox.digit2->setTextureRect(*toolbox.digit2rect);
    toolbox.digit3rect->left = mineCount[2]*21;
    toolbox.digit3->setTextureRect(*toolbox.digit3rect);
    toolbox.window.draw(*toolbox.digit1);
    toolbox.window.draw(*toolbox.digit2);
    toolbox.window.draw(*toolbox.digit3);
}
void load_board1(){
    //reset the new game button
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gamestate;
    toolbox.gamestate = new Gamestate("boards/testboard1.brd");
    auto ngb_texture = new sf::Texture;
    ngb_texture->loadFromFile("images/face_happy.png");
    auto ngb_sprite = new sf::Sprite(*ngb_texture);
    ngb_sprite->setPosition(toolbox.newGameButton->getPosition());
    toolbox.newGameButton->setSprite(ngb_sprite);
    toolbox.window.draw(*toolbox.newGameButton->getSprite());
    //Here we reset the mines
    resetDigits();
}
void load_board2(){
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gamestate;
    toolbox.gamestate = new Gamestate("boards/testboard2.brd");
    auto ngb_texture = new sf::Texture;
    ngb_texture->loadFromFile("images/face_happy.png");
    auto ngb_sprite = new sf::Sprite(*ngb_texture);
    ngb_sprite->setPosition(toolbox.newGameButton->getPosition());
    toolbox.newGameButton->setSprite(ngb_sprite);
    toolbox.window.draw(*toolbox.newGameButton->getSprite());
    //Here we reset the mines
    resetDigits();
}