#include "agent.h"

//int Agent::sAgentCount = 0;
//
//int Agent::sAgentCopied = 0;

Agent::Agent() : // jakos inaczej
    sf::CircleShape(), mSpeed(3), mAngle(0), mDestination(rand() % 6)
{
    setRadius(3.0f);
    setFillColor(sf::Color::Red);
    setPosition(RandomPos(WINDOW_WIDTH, WINDOW_HEIGHT));

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

float Agent::GetAngle() const{
    return mAngle * (M_PI / 180);
}
void Agent::SetAngle(float angle) {
    this->mAngle = angle * (180 / M_PI);
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

void Agent::SetDirection(const std::vector<Dest>& dests)
{
    double dy, dx;
    sf::Vector2f destCPos;

    if (mNearestTiles.size() < 1)
    {
        destCPos = dests[GetDestination()].GetCenterPosition();
        dy = GetCenterPosition().y - destCPos.y;
        dx = GetCenterPosition().x - destCPos.x;
        if (GetCenterPosition().x >= destCPos.x)
            SetAngle(atan(dy / dx) + M_PI);

        else
            SetAngle(atan(dy / dx));
    }
    else
    {
        int i = rand() % mNearestTiles.size();

        destCPos = mNearestTiles[i].GetCenterPosition();
        dy = GetCenterPosition().y - mNearestTiles[i].GetCenterPosition().y;
        dx = GetCenterPosition().x - mNearestTiles[i].GetCenterPosition().x;

        if (GetCenterPosition().x >= destCPos.x)
            SetAngle(atan(dy / dx) + M_PI);
        else
            SetAngle(atan(dy / dx));
    }
}

void Agent::ChangeDest(const std::vector<Dest>& dests)
{
    if (sqrt(pow(GetCenterPosition().x - dests[GetDestination()].GetCenterPosition().x, 2) + pow(GetCenterPosition().y - dests[GetDestination()].GetCenterPosition().y, 2)) < pow(GetSpeed(),2))
    {
        int randDest = 0;
        int randNumber = rand() % 100;
        for (int i = 0; i < dests.size(); i++)
        {
            if (randNumber < Dest::SumProbability(GetDestination(), i))
            {
                randDest = i;
                break;
            }
        }
        SetDestination(randDest);
    }
}


bool Agent::canNearestTiles(Tile tile, const std::vector<Dest>& dests) const
{
    float dist = Distance(GetCenterPosition(), tile.GetCenterPosition());
    if(tile.getFillColor() == Grey && dist < 10 * Tile::sHeight &&
        IsCloser(tile.GetCenterPosition(), GetCenterPosition(), dests[GetDestination()].GetCenterPosition()))
        return 1;
    else
        return 0;
}



bool inline IsCloser(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f target)
{
    return Distance(p1, target) < Distance(p2, target);
}

sf::Vector2f Agent::RandomPos(float width, float height)
{
    return sf::Vector2f(rand() % (int)(width - 2 * getRadius()), rand() % (int)(height - 2 * getRadius()));
}

double Distance(sf::Vector2f v1, sf::Vector2f v2) { // chyba nie potrzebuje
    return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}