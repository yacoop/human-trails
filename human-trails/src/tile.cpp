#include "tile.h"

const float Tile::sWidth = 10;
const float Tile::sHeight = 10;


Tile::Tile(float x = 0, float y = 0) :
    sf::RectangleShape(sf::Vector2f(sWidth, sHeight))
{
    setFillColor(Grey);
    setPosition(x, y);

    //sTileCount++;
}

//Tile::~Tile()
//{
//    sTileCount--;
//}
//
//Tile::Tile(Tile const& tile) :
//    sf::RectangleShape(tile), mGrassHeight(tile.mGrassHeight)
//{
//    sTileCopied++;
//	sTileCount++;
//}

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
}






