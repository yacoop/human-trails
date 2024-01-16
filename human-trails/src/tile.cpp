#include "tile.h"

const float Tile::sWidth = 10;
const float Tile::sHeight = 10;


Tile::Tile(float x = 0, float y = 0, State state = dirt) :
    sf::RectangleShape(sf::Vector2f(sWidth, sHeight))
{
    setPosition(x, y);
    this->state = state;
    //sTileCount++;

    if (state == pavement)
    {
		setFillColor(Grey);
	}
    else if (state == dirt)
    {
		setFillColor(Brown);
	}
    else
    {
		setFillColor(sf::Color::Red);
	}
}

sf::Vector2f Tile::GetCenterPosition() const{
    return getPosition() + getSize() * .5f;
}

float Tile::GetGrassHeight() const
{
    return mGrassHeight;
}

void Tile::SetGrassHeight(float grassHeight)
{
    this->mGrassHeight = grassHeight;
}

void Tile::Grow() {
    SetGrassHeight(GetGrassHeight() + 0.01);
}

void Tile::Stomp() {
    SetGrassHeight(GetGrassHeight() * mLambda);
    beenThere++;
}






