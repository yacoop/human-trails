#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <array>

constexpr float WINDOW_WIDTH = 800;
constexpr float WINDOW_HEIGHT = 800;

constexpr int MAP_WIDTH = 80;
constexpr int MAP_HEIGHT = 80;

constexpr int DEST_COUNT = 6;

constexpr float TILE_WIDTH = (WINDOW_WIDTH / MAP_WIDTH);
constexpr float TILE_HEIGHT = (WINDOW_HEIGHT / MAP_HEIGHT);

#define Grey sf::Color(128, 128, 128)

class Tile : public sf::RectangleShape
{
private:
    float mGrassHeight;
    double mLambda = 0.8;


public:
    Tile(float x, float y, float grass_height);
    ~Tile();
    Tile(Tile const& tile);
    sf::Vector2f GetCenterPosition();

    float GetGrassHeight() const;
    void SetGrassHeight(float grass_height);

    void Grow();
    void Stomp();

public:
    static int sTileCount;
    static int sTileCopied;

public:
    static Tile** mapInit();
    static void GrowGrass(Tile** map);
    static void DrawMap(sf::RenderWindow& App, Tile** map);

};

//utils
double Distance(sf::Vector2f v1, sf::Vector2f v2);

class Dest : public sf::CircleShape
{
public:
    Dest(float x, float y, float r);

    sf::Vector2f GetCenterPosition();

public:
    static Dest* Init();
    static int markov[6][6];
    static int SumProbability(int loc, int dest);

};


