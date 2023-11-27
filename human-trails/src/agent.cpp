#include "agent.h"

//int Agent::sAgentCount = 0;
//
//int Agent::sAgentCopied = 0;

Agent::Agent() : // jakos inaczej
    sf::CircleShape(), mSpeed(3), mAngle(0), mDestination(rand() % 6)
{
    setRadius(3.0f);
    setFillColor(sf::Color::Blue);
    setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

    //sAgentCount++;
}

sf::Vector2f Agent::GetCenterPosition() const{
    return getPosition() + sf::Vector2f(getRadius(), getRadius());
}

float Agent::GetSpeed() const {
    return mSpeed;
}
void Agent::SetSpeed(float speed) {
    this->mSpeed = speed;
}

float Agent::GetAngle() const{ //zwraca w radianach
    return mAngle;
}
void Agent::SetAngle(float angle) { //podaje w radianach
    this->mAngle = angle;
}

int Agent::GetDestination() const{
    return mDestination;
}

void Agent::SetDestination(int destination) {
    this->mDestination = destination;
}

void Agent::MoveAgent()
{
    move(GetSpeed() * cos(GetAngle()), GetSpeed() * sin(GetAngle()));
}


//void Agent::ChangeDest(const std::vector<Dest>& dests)
//{
//    if (Distance2(GetCenterPosition(), dests[GetDestination()].GetCenterPosition()) < pow(GetSpeed(), 2))
//    {
//        int randDest = 0;
//        double randNumber = (double) rand() / RAND_MAX;
//        std::cout << randNumber << std::endl;
//        for (int i = 0; i < dests.size(); i++)
//        {
//            if (randNumber < Dest::SumProbability(GetDestination(), i))
//            {
//                std::cout << randNumber << " " << Dest::SumProbability(GetDestination(), i) << " "  << i << std::endl;
//                randDest = i;
//                break;
//            }
//            //zle cso xD
//
//        }
//        std::cout << "jesli wyzej nie bylo dlugiego outputu to co jest nie tal" << std::endl;
//        SetDestination(randDest);
//    }
//}

void Agent::ChangeDest(const std::vector<Dest>& dests)
{
    if (Distance2(GetCenterPosition(), dests[GetDestination()].GetCenterPosition()) < pow(GetSpeed(), 2))
    {
        int randDest = 0;
        double randNumber = (double)rand() / RAND_MAX;
        //std::cout << randNumber << std::endl;
        for (int i = 0; i < dests.size(); i++)
        {
            randNumber -= Dest::markov[GetDestination()][i];
            if (randNumber < 0)
            {
                //std::cout << randNumber << " " << Dest::SumProbability(GetDestination(), i) << " " << i << std::endl;
                randDest = i;
                break;
            }
            //zle cso xD

        }
        //std::cout << "jesli wyzej nie bylo dlugiego outputu to co jest nie tal" << std::endl;
        SetDestination(randDest);
    }
}


bool Agent::canNearestTiles(Tile tile, const std::vector<Dest>& dests) const
{
    float dist2 = Distance2(GetCenterPosition(), tile.GetCenterPosition());
    if((tile.getFillColor() == Brown || tile.getFillColor() == Grey) && dist2 < pow(10 * Tile::sHeight,2) &&
        IsCloser(tile.GetCenterPosition(), GetCenterPosition(), dests[GetDestination()].GetCenterPosition()))
        return 1;
    else
        return 0;
}



bool inline IsCloser(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f target)
{
    return Distance2(p1, target) < Distance2(p2, target);
}

sf::Vector2f Agent::RandomPos(float width, float height)
{
    return sf::Vector2f(rand() % (int)(width - 2 * getRadius()), rand() % (int)(height - 2 * getRadius()));
}

double Distance2(const sf::Vector2f v1, const sf::Vector2f v2){ // chyba nie potrzebuje
    return pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2);
}