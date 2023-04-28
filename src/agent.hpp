#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define agents_count 20


class Agent: public sf::CircleShape{
    private:
        float speed;
        float angle;
        int destination;
        sf::Vector2f dest;
        std::vector<Tile> nearest_tiles;

    public:
        Agent(float x, float y, int dest, float speed, float angle,
            float r, sf::Color color);

        sf::Vector2f getCenterPosition();
        Tile* getTile(Tile** map);
        float getSpeed();
        void setSpeed(float speed);

        float getAngle();
        void setAngle(float angle);

        int getDestination();
        void setDestination(int destination);

        void moveAgent();

        void setDirection(Dest* dests);

        void changeDest(Dest* dests);

        void setNearestTiles(Tile** map, Dest* dests);
};

Agent* agentsInit();

void manageAgents(Agent* agents, Tile** map, Dest* dests);

void drawObjects(sf::RenderWindow &App, Agent* agents, Dest* dests);

void stompGrass(Tile** map, Agent* agents);
