#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define window_width 1600
#define window_height 800

#define map_width 160
#define map_height 80

#define tile_width (window_width/map_width) //to chyba powinno byc jako zmienna ale to na pozniej
#define tile_height (window_height/map_height)

#define Grey sf::Color(128, 128, 128)

class Tile: public sf::RectangleShape{
    private:
        float grass_height;
        double lambda = 0.9;

    public:
        Tile(float x, float y, float grass_height);

        sf::Vector2f getCenterPosition();

        float getGrassHeight();
        void setGrassHeight(float grass_height);

        void grow();
        void stomp();
};

Tile** mapInit();

void growGrass(Tile** map);

void drawMap(sf::RenderWindow &App, Tile** map);

//utils
double distance(sf::Vector2f v1, sf::Vector2f v2);

