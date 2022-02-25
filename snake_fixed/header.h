#pragma once
#ifndef header_h
#define header_h
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <time.h>
#include <string>

class Node
{
public:
    float x, y;
};


void move(Node body[], int direction, sf::Time,bool);
int eat(Node body[], Node& apple, int& snakeLength, int& score,sf::Sound &point, bool audio);
bool checkGame(Node body[], int, int, sf::Clock &gameTime, bool);
void roundFunc(Node body[], int direction);
void gameOver(bool &game, sf::RenderWindow& window,sf::Clock &gameTime, Node body[], int &snakeLength, int &score, int &direction, bool & horizontal, bool &vertical, sf::Clock &deltaClock, sf::Sound& point, bool audio);
int mainMenu(sf::RenderWindow &window, sf::Music &music, bool &audio, sf::Sound& point);
struct stop_now_t { };




#endif