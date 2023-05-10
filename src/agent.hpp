#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define agents_count 100

class Agent : public sf::CircleShape {
private:
    float m_speed;
    float m_angle;
    int m_destination;
    sf::Vector2f m_dest;
    std::vector<Tile> m_nearestTiles;

public:
    Agent(float x, float y, int dest, float speed, float angle,
        float r, sf::Color color);

    sf::Vector2f getCenterPosition();
    Tile* getTile(Tile** map);
    float getSpeed() const;
    void setSpeed(float speed);

    float getAngle();
    void setAngle(float angle);

    int getDestination();
    void setDestination(int destination);

    void moveAgent();

    void setDirection(Dest* dests);

    void changeDest(Dest* dests);

    void setNearestTiles(Tile** map, Dest* dests);

    static int agentCount;

public:
    static Agent* init();

    static void manage(Agent* agents, Tile** map, Dest* dests);

    static void stompGrass(Tile** map, Agent* agents);
};

void drawObjects(sf::RenderWindow& App, Agent* agents, Dest* dests);

