#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <array>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

constexpr int MAP_WIDTH = 80;
constexpr int MAP_HEIGHT = 80;

constexpr int dests_count = 5;

#define TILE_WIDTH (WINDOW_WIDTH/MAP_WIDTH) 
#define TILE_HEIGHT (WINDOW_HEIGHT/MAP_HEIGHT)

#define Grey sf::Color(128, 128, 128)

class Tile : public sf::RectangleShape
{
private:
    float m_grassHeight;
    double m_lambda = 0.8;


public:
    Tile(float x, float y, float grass_height);

    sf::Vector2f getCenterPosition();

    float getGrassHeight() const;
    void setGrassHeight(float grass_height);

    void grow();
    void stomp();

    static int tileCount;

public:
    static Tile** mapInit();
    static void growGrass(Tile** map);
    static void drawMap(sf::RenderWindow& App, Tile** map);

};

void growGrass(Tile** map);
void drawMap(sf::RenderWindow& App, Tile** map);

//utils
double distance(sf::Vector2f v1, sf::Vector2f v2);

class Dest : public sf::CircleShape
{
public:
    Dest(float x, float y, float r);

    sf::Vector2f getCenterPosition();

public:
    static Dest* init();

};


