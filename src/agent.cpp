#include "agent.hpp"

int Agent::agentCount = 0;

Agent::Agent(float x = 0, float y = 0, int dest = 0, float speed = 0.1, float angle = 0,
    float r = 3.0f, sf::Color color = sf::Color::Red) :
    sf::CircleShape(), m_speed(speed), m_angle(angle), m_destination(dest)
{
    setRadius(r);
    setFillColor(color);
    setPosition(x, y);

    agentCount++;
}

sf::Vector2f Agent::getCenterPosition() {
    return getPosition() + sf::Vector2f(getRadius(), getRadius());
}

Tile* Agent::getTile(Tile** map) {
    int x, y;
    x = (int)getCenterPosition().x / TILE_WIDTH;
    y = (int)getCenterPosition().y / TILE_HEIGHT;
    return &map[x][y];
}


float Agent::getSpeed() const {
    return m_speed;
}
void Agent::setSpeed(float speed) {
    this->m_speed = speed;
}

float Agent::getAngle() {
    return m_angle * (M_PI / 180);
}
void Agent::setAngle(float angle) {
    this->m_angle = angle * (180 / M_PI);
}

int Agent::getDestination() {
    return m_destination;
}

void Agent::setDestination(int destination) {
    this->m_destination = destination;
}

void Agent::moveAgent()
{
    move(getSpeed() * cos(getAngle()), getSpeed() * sin(getAngle()));
}

void Agent::setDirection(Dest* dests)
{
    double dy, dx;
    sf::Vector2f destCPos;

    if (m_nearestTiles.size() < 2)
    {
        destCPos = dests[getDestination()].getCenterPosition();
        dy = getCenterPosition().y - destCPos.y;
        dx = getCenterPosition().x - destCPos.x;
        if (getCenterPosition().x >= destCPos.x)
            setAngle(atan(dy / dx) + M_PI);

        else
            setAngle(atan(dy / dx));
    }
    else
    {
        int i = rand() % m_nearestTiles.size();

        destCPos = m_nearestTiles[i].getCenterPosition();
        dy = getCenterPosition().y - m_nearestTiles[i].getCenterPosition().y;
        dx = getCenterPosition().x - m_nearestTiles[i].getCenterPosition().x;

        if (getCenterPosition().x >= destCPos.x)
            setAngle(atan(dy / dx) + M_PI);
        else
            setAngle(atan(dy / dx));
    }
}

void Agent::changeDest(Dest* dests)
{
    if (sqrt(pow(getCenterPosition().x - dests[getDestination()].getCenterPosition().x, 2) + pow(getCenterPosition().y - dests[getDestination()].getCenterPosition().y, 2)) < getSpeed())
    {
        int rand_dest;
        do {
            rand_dest = rand() % dests_count;
        } while (rand_dest == getDestination());
        setDestination(rand_dest);
    }
}

void Agent::setNearestTiles(Tile** map, Dest* dests)
{
    m_nearestTiles.clear();

    // jako funkcja?
    int x = (int)(getCenterPosition().x / TILE_WIDTH);
    int y = (int)(getCenterPosition().y / TILE_HEIGHT);
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
            //jakos ladniej zapisac
            if (map[j][k].getFillColor() == Grey && distance(getCenterPosition(), map[j][k].getCenterPosition()) < 10 * TILE_HEIGHT && distance(getCenterPosition(), dests[getDestination()].getCenterPosition()) > distance(map[j][k].getCenterPosition(), dests[getDestination()].getCenterPosition()))
            {
                m_nearestTiles.push_back(map[j][k]);
                // map[j][k].setFillColor(sf::Color::Blue); // to color nearest tiles
            }
        }
    }
}

Agent* Agent::init() {
    Agent* agents = new Agent[agents_count];
    for (int i = 0; i < agents_count; i++)
    {
        agents[i] = Agent(rand() % (int)(WINDOW_WIDTH - 2 * agents[i].getRadius()), rand() % (int)(WINDOW_HEIGHT - 2 * agents[i].getRadius()),
            rand() % dests_count, 3, rand() % 360);
    }
    return agents;
}


void Agent::manage(Agent* agents, Tile** map, Dest* dests)
{

    int x, y;
    for (int i = 0; i < agents_count; i++)
    {
        agents[i].getTile(map)->stomp();
        //setting nearest tiles
        agents[i].setNearestTiles(map, dests);
        //setting destination
        agents[i].setDirection(dests);
        // destination reached
        agents[i].changeDest(dests);
        // agent movement
        agents[i].moveAgent();
    }
}

void drawObjects(sf::RenderWindow& App, Agent* agents, Dest* dests)
{

    for (int i = 0; i < agents_count; i++)
    {
        App.draw(agents[i]);
    }
    for (int i = 0; i < dests_count; i++)
    {
        App.draw(dests[i]);
    }
}
