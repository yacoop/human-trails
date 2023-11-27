#include "dest.h"

Dest::Dest(float x = 0, float y = 0) :
    sf::CircleShape(5)
{
    // setRadius(r);
    setFillColor(sf::Color::Black);
    setPosition(x, y);
}

sf::Vector2f Dest::GetCenterPosition() const {
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

//init for testing
//void Dest::Init(std::vector<Dest> dests, int size) {
//    for (int i = 0; i < size; i++)
//    {
//        dests.push_back(Dest());
//        dests[i].setPosition(WINDOW_WIDTH / 2 + 250 * cos(2 * M_PI * i / size - M_PI / 2), WINDOW_HEIGHT / 2 + 250 * sin(2 * M_PI * i / size - M_PI / 2));
//    }
//}

//init that corresponds to the field
//Dest* Dest::Init() {
//    Dest* dests;
//    dests = new Dest[6];
//    dests[0] = Dest(0.38 * WINDOW_WIDTH, 0.18 * WINDOW_HEIGHT); //mini
//    dests[1] = Dest(0.28 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT); //fizya
//    dests[2] = Dest(0.1 * WINDOW_WIDTH, 0.75 * WINDOW_HEIGHT); //wibhis
//    dests[3] = Dest(0.45 * WINDOW_WIDTH, 0.8 * WINDOW_HEIGHT); //mechanika
//    dests[4] = Dest(0.63 * WINDOW_WIDTH, 0.44 * WINDOW_HEIGHT); //chemia
//    dests[5] = Dest(0.92 * WINDOW_WIDTH, 0.78 * WINDOW_HEIGHT); //gg
//    return dests;
//}

//void Dest::Init(std::vector<Dest>& dests, int size) {
//    dests.push_back(Dest(0.38 * WINDOW_WIDTH, 0.18 * WINDOW_HEIGHT)); //mini
//    dests.push_back(Dest(0.28 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT)); //fizyka
//    dests.push_back(Dest(0.1 * WINDOW_WIDTH, 0.75 * WINDOW_HEIGHT)); //wibhis
//    dests.push_back(Dest(0.45 * WINDOW_WIDTH, 0.8 * WINDOW_HEIGHT)); //mechanika
//    dests.push_back(Dest(0.63 * WINDOW_WIDTH, 0.44 * WINDOW_HEIGHT)); //chemia
//    dests.push_back(Dest(0.92 * WINDOW_WIDTH, 0.78 * WINDOW_HEIGHT)); //gg
//}



//mini  fiza   wibhis   mech     chem    gg
int Dest::markov[6][6] = { {0,     10,     5,      5,      10,     70},  //mini
                             {10,    0,      11,     2,      7,      70},  //fiza
                             {5,     5,      0,      10,     10,     70},  //wibhis
                             {5,     5,      10,     0,      10,     70},  //mech
                             {0,     10,     15,    15,      0,      60},  //chem
                             {30,    20,     10,    10,      30,     0}, }; //gg

int Dest::SumProbability(int loc, int dest)
{
    int sum = 0;
    for (int i = 0; i < dest; i++)
        sum += markov[loc][i];
    return sum;
}