#include "agent.hpp"

int Agent::sAgentCount = 0;

int Agent::sAgentCopied = 0;

Agent::Agent() :
    sf::CircleShape(), mSpeed(3), mAngle(0), mDestination(rand() % DESTS_COUNT)
{
    setRadius(3.0f);
    setFillColor(sf::Color::Red);
    setPosition(rand() % (int)(WINDOW_WIDTH - 2 * getRadius()), rand() % (int)(WINDOW_HEIGHT - 2 * getRadius()));

    sAgentCount++;
}

Agent::Agent(float speed, float angle = 0, float r = 3.0f, sf::Color color = sf::Color::Red) :
    sf::CircleShape(), mSpeed(speed), mAngle(angle), mDestination(rand() % DESTS_COUNT)
{
    setRadius(r);
    setFillColor(color);
    setPosition(rand() % (int)(WINDOW_WIDTH - 2 * getRadius()), rand() % (int)(WINDOW_HEIGHT - 2 * getRadius()));

    sAgentCount++;
}

Agent::~Agent() {
	sAgentCount--;
}

Agent::Agent(Agent const& agent) :
    sf::CircleShape(agent), mSpeed(agent.mSpeed), mAngle(agent.mAngle),
    mDestination(agent.mDestination)
{
    sAgentCount++;
    sAgentCopied++;
}

sf::Vector2f Agent::GetCenterPosition() const{
    return getPosition() + sf::Vector2f(getRadius(), getRadius());
}

Tile* Agent::GetTile(Tile** map) {
    int x, y;
    x = (int)GetCenterPosition().x / TILE_WIDTH;
    y = (int)GetCenterPosition().y / TILE_HEIGHT;
    return &map[x][y];
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

    if (mNearestTiles.size() < 2)
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
    if (sqrt(pow(GetCenterPosition().x - dests[GetDestination()].GetCenterPosition().x, 2) + pow(GetCenterPosition().y - dests[GetDestination()].GetCenterPosition().y, 2)) < GetSpeed())
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

void Agent::SetNearestTiles(Tile** map, const std::vector<Dest>& dests)
{
    mNearestTiles.clear();

    // jako funkcja?
    int x = (int)(GetCenterPosition().x / TILE_WIDTH);
    int y = (int)(GetCenterPosition().y / TILE_HEIGHT);
    int x_min, x_max, y_min, y_max;

    //setting iteration range
    if (x < 10) x_min = 0;
    else x_min = x - 10;

    if (x > (MAP_WIDTH - 10)) x_max = MAP_WIDTH;
    else x_max = x + 10;

    if (y < 10) y_min = 0;
    else y_min = y - 10;

    if (y > (MAP_HEIGHT - 10)) y_max = MAP_HEIGHT;
    else y_max = y + 10;


    for (int j = x_min; j < x_max; j++)
    {
        for (int k = y_min; k < y_max; k++)
        {
            if(canNearestTiles(map[j][k], dests))
            {
                mNearestTiles.push_back(map[j][k]);
                //map[j][k].setFillColor(sf::Color::Blue); // to color nearest tiles
            }
        }
    }
}

bool Agent::canNearestTiles(Tile tile, const std::vector<Dest>& dests) const
{
    float dist = Distance(GetCenterPosition(), tile.GetCenterPosition());
    if(tile.getFillColor() == Grey && dist < 10 * TILE_HEIGHT &&
        isCloser(tile.GetCenterPosition(), GetCenterPosition(), dests[GetDestination()].GetCenterPosition()))
        return 1;
    else
        return 0;
}

bool isCloser(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f target)
{
	return Distance(p1, target) < Distance(p2, target);
}



void Agent::Init(std::vector<Agent>& agents, int size) {
    for (int i = 0; i < size; i++)
    {
        agents.push_back(Agent());
    }
}

void Agent::Manage(std::vector<Agent>& agents, Tile** map, const std::vector<Dest>& dests)
{

    int x, y;
    for (int i = 0; i < agents.size(); i++)
    {
        agents[i].GetTile(map)->Stomp();
        //setting nearest tiles
        agents[i].SetNearestTiles(map, dests);
        //setting destination
        agents[i].SetDirection(dests);
        // destination reached
        agents[i].ChangeDest(dests);
        // agent movement
        agents[i].MoveAgent();
    }
}

void DrawObjects(sf::RenderWindow& App, const std::vector<Agent>& agents, const std::vector<Dest>& dests)
{

    for (int i = 0; i < agents.size(); i++)
    {
        App.draw(agents[i]);
    }
    for (int i = 0; i < dests.size(); i++)
    {
        App.draw(dests[i]);
    }
}

