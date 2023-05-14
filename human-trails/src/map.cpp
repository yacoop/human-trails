#include "map.hpp"

int Tile::sTileCount = 0;

int Tile::sTileCopied = 0;

Tile::Tile(float x = 0, float y = 0, float grass_height = 0) :
    sf::RectangleShape(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT)), mGrassHeight(grass_height)
{
    setFillColor(Grey);
    setPosition(x, y);

    sTileCount++;
}

Tile::~Tile()
{
    sTileCount--;
}

Tile::Tile(Tile const& tile) :
    sf::RectangleShape(tile), mGrassHeight(tile.mGrassHeight)
{
    sTileCopied++;
	sTileCount++;
}

sf::Vector2f Tile::GetCenterPosition() {
    return getPosition() + getSize() * .5f;
}

float Tile::GetGrassHeight() const
{
    return mGrassHeight;
}

void Tile::SetGrassHeight(float grass_height)
{
    this->mGrassHeight = grass_height;
}

void Tile::Grow() {
    SetGrassHeight(GetGrassHeight() + 0.01);
}

void Tile::Stomp() {
    SetGrassHeight(GetGrassHeight() * mLambda);
}

Tile** Tile::mapInit() {
    Tile** map = new Tile* [MAP_WIDTH];
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        map[i] = new Tile[MAP_HEIGHT];
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            map[i][j] = Tile(i * TILE_WIDTH, j * TILE_HEIGHT);
        }
    }
    return map;
}



void Tile::GrowGrass(Tile** map) {
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            if (map[i][j].GetGrassHeight() < 2)
            {
                map[i][j].setFillColor(Grey);
                map[i][j].Grow();
            }
            else
                map[i][j].setFillColor(sf::Color::Green);
        }
    }
}

void Tile::DrawMap(sf::RenderWindow& App, Tile** map) {
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
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

sf::Vector2f Dest::GetCenterPosition() {
    return getPosition() + sf::Vector2f(getRadius(), getRadius());
}


//init for testing
//Dest* Dest::Init() {
//    Dest* dests;
//    dests = new Dest[DEST_COUNT];
//    for (int i = 0; i < DEST_COUNT; i++)
//    {
//        dests[i] = Dest();
//        dests[i].setPosition(WINDOW_WIDTH / 2 + 250 * cos(2 * M_PI * i / DEST_COUNT - M_PI / 2), WINDOW_HEIGHT / 2 + 250 * sin(2 * M_PI * i / DEST_COUNT - M_PI / 2));
//    }
//    return dests;
//}

//init that corresponds to the field
Dest* Dest::Init() {
    Dest* dests;
    dests = new Dest[6];
    dests[0] = Dest(0.38 * WINDOW_WIDTH, 0.18 * WINDOW_HEIGHT); //mini
    dests[1] = Dest(0.28 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT); //fizya
    dests[2] = Dest(0.1 * WINDOW_WIDTH, 0.75 * WINDOW_HEIGHT); //wibhis
    dests[3] = Dest(0.45 * WINDOW_WIDTH, 0.8 * WINDOW_HEIGHT); //mechanika
    dests[4] = Dest(0.63 * WINDOW_WIDTH, 0.44 * WINDOW_HEIGHT); //chemia
    dests[5] = Dest(0.92 * WINDOW_WIDTH, 0.78 * WINDOW_HEIGHT); //gg
    return dests;
}

                             //mini  fiza   wibhis   mech     chem    gg
int Dest::markov[6][6] = { {0,     10,     5,      5,      10,     6},  //mini
                             {10,    0,      11,     2,      7,      70},  //fiza
                             {5,     5,      0,      10,     10,     70},  //wibhis
                             {5,     5,      10,     0,      10,     70},  //mech
                             {0,     10,     15,    15,      0,      60},  //chem
                             {30,    20,     10,    10,      30,     00}, }; //gg

int Dest::SumProbability(int loc, int dest)
{
    int sum = 0;
    for (int i = 0; i < dest; i++)
        sum += markov[loc][i];
    return sum;
}

//utils
double Distance(sf::Vector2f v1, sf::Vector2f v2) {
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}



