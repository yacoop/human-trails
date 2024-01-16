#include "dest.h"

Dest::Dest(float x = 0, float y = 0) :
    sf::CircleShape(5)
{
    setFillColor(sf::Color::Black);
    setPosition(x, y);
}

sf::Vector2f Dest::GetCenterPosition() const
{
    return getPosition() + sf::Vector2f(getRadius(), getRadius());
}


//                            //mini  fiza   wibhis   mech     chem    gg
double Dest::markov[6][6] = {   {0,    .05,    .05,    .05,    .05,    .80},  //mini
                             {.05,  .05,    .10,    .05,    .05,    .70},  //fiza
                             {.05,  .05,    .0,     .05,    .05,    .80},  //wibhis
                             {.05,  .05,    .10,    0,      .10,    .70},  //mech
                             {.05,  .10,    .15,    .10,    0,      .60},  //chem
                             {.30,  .10,    .40,    .05,    .15,    0}, }; //gg

double Dest::SumProbability(int loc, int dest)
{
    double sum = 0;
    for (int i = 0; i < dest; i++)
        sum += markov[loc][i];
    return sum;
}