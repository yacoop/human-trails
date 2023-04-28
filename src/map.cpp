#include "map.hpp"

Tile::Tile(float x = 0, float y = 0, float grass_height = 0){
    RectangleShape();
    setSize(sf::Vector2f(tile_width, tile_height));
    setFillColor(Grey);
    setPosition(x, y);
    this->grass_height = 1;
}

sf::Vector2f Tile::getCenterPosition(){
    return getPosition()+getSize()*.5f;
    // return getPosition();
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

Dest::Dest(float x = 0, float y = 0, float r = 5){
    CircleShape();
    setRadius(r);
    setFillColor(sf::Color::Black);
    setPosition(x, y);
}

sf::Vector2f Dest::getCenterPosition(){
    return getPosition()+sf::Vector2f(getRadius(), getRadius());
    // return getPosition();
}

Dest* destsInit(){
    Dest* dests;
    dests =  new Dest[dests_count];
    for(int i = 0; i < dests_count; i++)
    {
        dests[i] = Dest();
        dests[i].setPosition(window_width/2 +250*cos(2*M_PI*i/dests_count-M_PI/2), window_height/2 +250*sin(2*M_PI*i/dests_count-M_PI/2));
    }
    return dests;
}

//utils
double distance(sf::Vector2f v1, sf::Vector2f v2){
    return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2));
}

