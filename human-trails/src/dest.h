#pragma once

#include "common.h"

class Dest : public sf::CircleShape
{
public:
    Dest(float x, float y);

    sf::Vector2f GetCenterPosition() const;

public:
    static double markov[6][6];
    static double SumProbability(int loc, int dest);
};