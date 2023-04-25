#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define agents_count 10
#define dests_count 4

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

        float getSpeed();
        void setSpeed(float speed);

        float getAngle();
        void setAngle(float angle);

        int getDestination();
        void setDestination(int destination);

        void moveAgent();

        void setDirection(sf::CircleShape* dests);

        void changeDest(sf::CircleShape* dests);

        void setNearestTiles(Tile** map, sf::CircleShape* dests);
};

Agent* agentsInit();

sf::CircleShape* destsInit();

void manageAgents(Agent* agents, Tile** map, sf::CircleShape* dests);

void drawObjects(sf::RenderWindow &App, Agent* agents, sf::CircleShape* dests);

void stompGrass(Tile** map, Agent* agents);
