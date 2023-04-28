#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define window_width 800
#define window_height 800

#define map_width 80
#define map_height 80

#define dests_count 3

#define tile_width (window_width/map_width) 
#define tile_height (window_height/map_height)

#define Grey sf::Color(128, 128, 128)

class Tile: public sf::RectangleShape{
    private:
        float grass_height;
        double lambda = 0.8;

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

class Dest: public sf::CircleShape{
    public:
        Dest(float x, float y, float r);

        sf::Vector2f getCenterPosition();
};

Dest* destsInit();

