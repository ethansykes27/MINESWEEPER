#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
class Gamestate{
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    Gamestate(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    Gamestate(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
    sf::Vector2i get_dimensions();
    friend class Tile;
    friend class Toolbox;
    ~Gamestate();

private:
    PlayStatus play_status;
    vector<Tile*> tile_list;
    sf::Vector2i _dimensions;
    int numberOfMines;
    vector<bool> boardVector;
};