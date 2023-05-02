#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

int launch();
void restart();
void render();
void toggleDebugMode();
bool getDebugMode();
int gameLoop();
void resetDigits(); // resets the digits on the mine counter
void load_board1();
void load_board2();


