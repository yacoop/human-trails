#pragma once

#include <iostream>
#include <cmath>
#include <ctime>
#include <array>

#include "common.h"

#define Grey sf::Color(128, 128, 128)

class Tile : public sf::RectangleShape
{
public:
    Tile(float x, float y);
    //~Tile();
    //Tile(Tile const& tile);


    sf::Vector2f GetCenterPosition() const;

    float GetGrassHeight() const;
    void SetGrassHeight(float grass_height);

    void Grow();
    void Stomp();

public:
    static const float sWidth;
    static const float sHeight;

private:
    float mGrassHeight = 0;
    float mLambda = 0.8f;
};






