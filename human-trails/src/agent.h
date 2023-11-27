#pragma once

#include "dest.h"
#include "tile.h"
#include "common.h"


constexpr auto AGENTS_COUNT = 100;

class Agent : public sf::CircleShape {


public:
    std::vector<Tile> mNearestTiles;
    Agent();
    //Agent(float speed, float angle,
    //    float r, sf::Color color);
    //~Agent();
    //Agent(Agent const& agent);

    sf::Vector2f GetCenterPosition() const;

    float GetSpeed() const;
    void SetSpeed(float speed);

    float GetAngle() const;
    void SetAngle(float angle);

    int GetDestination() const;
    void SetDestination(int destination);

    void MoveAgent();

    void SetDirection(const std::vector<Dest>& dests);

    void ChangeDest(const std::vector<Dest>& dests);
    bool canNearestTiles(Tile tile, const std::vector<Dest>& dests) const;

public:
    sf::Vector2f RandomPos(float width, float height);

private:
    float mSpeed;
    float mAngle;
    int mDestination;
};

bool inline IsCloser(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f target);
double Distance2(const sf::Vector2f v1, const sf::Vector2f v2);
