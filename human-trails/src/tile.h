#pragma once

#include "common.h"

#define Grey sf::Color(128, 128, 128)
#define Brown sf::Color(70, 60, 42)
#define Green sf::Color(30, 150, 15)

enum State { pavement = 0, dirt };

class Tile : public sf::RectangleShape
{
public:
    Tile(float x, float y, State state);

    sf::Vector2f GetCenterPosition() const;

    float GetGrassHeight() const;
    void SetGrassHeight(float grass_height);

    void Grow();
    void Stomp();

public:
    static const float sWidth;
    static const float sHeight;
    State state = dirt;
    //bool state = 1;

private:
    float mGrassHeight = 0;
    float mLambda = 0.8f;
};






