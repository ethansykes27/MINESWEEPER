#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
class Tile{
public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
    friend class Gamestate;
    friend class Toolbox;
    ~Tile();
private:
    std::array<Tile*,8> neighborArray{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
    void revealNeighbors();
    sf::Vector2f _position;
    State _state;
    sf::Sprite* curr_sprite = nullptr;
    sf::Sprite* hidden_sprite;
    sf::Sprite* revealed_sprite;
    sf::Sprite* flag_sprite;
    bool is_mine;// stores whether the tile is a mine
    bool neighbors_set=false;
    sf::Sprite* exploded_sprite;
    bool flagged = false; //stores whether or not the tile is flagged before entering debugged mode
};
