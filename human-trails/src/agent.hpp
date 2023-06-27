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

    sf::Vector2f GetCenterPosition() const;
    Tile* GetTile(Tile** map);

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
    void SetNearestTiles(Tile** map, const std::vector<Dest>& dests);

public:
    static int sAgentCount;
    static int sAgentCopied;

public:
    static void Init(std::vector<Agent>& agents, int size);

    static void Manage(std::vector<Agent>& agents, Tile** map, const std::vector<Dest>& dests);
};

void DrawObjects(sf::RenderWindow& App, const std::vector<Agent>& agents, const std::vector<Dest>& dests);
bool isCloser(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f target);
