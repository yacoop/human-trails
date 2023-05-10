#include "map.hpp"

int Tile::tileCount = 0;

Tile::Tile(float x = 0, float y = 0, float grass_height = 0) :
        sf::RectangleShape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT)), m_grassHeight(grass_height)
{
    setFillColor(Grey);
    setPosition(x, y);

    tileCount++;
}

sf::Vector2f Tile::getCenterPosition(){
    return getPosition()+getSize()*.5f;
}

float Tile::getGrassHeight() const
{
    return m_grassHeight;
}

void Tile::setGrassHeight(float grass_height)
{
    this->m_grassHeight = grass_height;
}

void Tile::grow(){
    setGrassHeight(getGrassHeight()+0.01);
}

void Tile::stomp(){
    setGrassHeight(getGrassHeight()*m_lambda);
}

Tile** Tile::mapInit(){
    Tile** map = new Tile*[MAP_WIDTH];
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        map[i] = new Tile[MAP_HEIGHT];
        std::cout << Tile::tileCount << std::endl;
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            map[i][j] = Tile((double)i*TILE_WIDTH, j*TILE_HEIGHT);
        }
    }
    return map;
}

void Tile::growGrass(Tile** map){
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
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

void Tile::drawMap(sf::RenderWindow &App, Tile** map){
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            App.draw(map[i][j]);
        }
    }
}

Dest::Dest(float x = 0, float y = 0, float r = 5) :
        sf::CircleShape(r) 
{
    // setRadius(r);
    setFillColor(sf::Color::Black);
    setPosition(x, y);
}

sf::Vector2f Dest::getCenterPosition(){
    return getPosition()+sf::Vector2f(getRadius(), getRadius());
}

Dest* Dest::init(){
    Dest* dests;
    dests =  new Dest[dests_count];
    for(int i = 0; i < dests_count; i++)
    {
        dests[i] = Dest();
        dests[i].setPosition(WINDOW_WIDTH/2 +250*cos(2*M_PI*i/dests_count-M_PI/2), WINDOW_HEIGHT/2 +250*sin(2*M_PI*i/dests_count-M_PI/2));
    }
    return dests;
}

//utils
double distance(sf::Vector2f v1, sf::Vector2f v2){
    return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2));
}

