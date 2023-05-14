#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <array>

constexpr auto AGENTS_COUNT = 100;

class Agent : public sf::CircleShape {
private:
    float mSpeed;
    float mAngle;
    int mDestination;
    std::vector<Tile> mNearestTiles;

public:
    Agent();
    Agent(float speed, float angle,
        float r, sf::Color color);
    ~Agent();
    Agent(Agent const& agent);

    sf::Vector2f GetCenterPosition();
    Tile* GetTile(Tile** map);
    float GetSpeed() const;
    void SetSpeed(float speed);

    float GetAngle();
    void SetAngle(float angle);

    int GetDestination();
    void SetDestination(int destination);

    void MoveAgent();

    void SetDirection(Dest* dests);

    void ChangeDest(Dest* dests);

    void SetNearestTiles(Tile** map, Dest* dests);

public:
    static int sAgentCount;
    static int sAgentCopied;

public:
    static void Init(std::vector<Agent>& agents, int size);

    static void Manage(std::vector<Agent>& agents, Tile** map, Dest* dests);
};

void DrawObjects(sf::RenderWindow& App, std::vector<Agent> agents, Dest* dests);

