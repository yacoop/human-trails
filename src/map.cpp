#include "map.hpp"

// const sf::Color Grey = sf::Color(128, 128, 128);

Tile::Tile(float x = 0, float y = 0, float grass_height = 0){
    RectangleShape();
    setSize(sf::Vector2f(tile_width, tile_height));
    setFillColor(Grey);
    setPosition(x, y);
    this->grass_height = 1;
}

sf::Vector2f Tile::getCenterPosition(){
    return getPosition()+getSize()*.5f;
}

float Tile::getGrassHeight(){
    return grass_height;
}

void Tile::setGrassHeight(float grass_height){
    this->grass_height = grass_height;
}

void Tile::grow(){
    setGrassHeight(getGrassHeight()+0.01);
}

void Tile::stomp(){
    setGrassHeight(getGrassHeight()*lambda);
}

Tile** mapInit(){
    static Tile** map = new Tile*[map_width];
    for(int i = 0; i < map_width; i++)
    {
        map[i] = new Tile[map_height];
        for(int j = 0; j < map_height; j++)
        {
            map[i][j] = Tile((double)i*tile_width, j*tile_height, 0);
        }
    }
    return map;
}

void growGrass(Tile** map){
    for(int i = 0; i < map_width; i++)
    {
        for(int j = 0; j < map_height; j++)
        {
            if(map[i][j].getGrassHeight() < 2) 
            {
                map[i][j].setFillColor(Grey);
                map[i][j].grow();
            }
            else
                map[i][j].setFillColor(sf::Color::Green);
        }
    }
}

void drawMap(sf::RenderWindow &App, Tile** map){
    for(int i = 0; i < map_width; i++)
    {
        for(int j = 0; j < map_height; j++)
        {
            App.draw(map[i][j]);
        }
    }
}

//utils
double distance(sf::Vector2f v1, sf::Vector2f v2){
    return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2));
}

