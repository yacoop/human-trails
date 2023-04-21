#pragma once

#include "map.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

#define agents_count 50
#define dests_count 4

class Agent: public sf::CircleShape{
    private:
    float speed;
    float angle;
    int destination;
    sf::Vector2f dest;
    std::vector<Tile> nearest_tiles;

    public:
        Agent(float x = 0, float y = 0, int dest = 0, float speed = 0.1, float angle = 0,
            float r = 3, sf::Color color = sf::Color::Red)
        {
            CircleShape();
            setRadius(r);
            setFillColor(sf::Color::Red);
	        setPosition(x, y);

            this->speed = speed;
            this->angle = angle;
            this->destination = dest;
        }

        float getSpeed(){
            return speed;
        }
        void setSpeed(float speed){
            this->speed = speed;
        }

        float getAngle(){
            return angle*(M_PI/180);
        }
        void setAngle(float angle){
            this->angle = angle*(180/M_PI);
        }

        int getDestination(){
            return destination;
        }

        void setDestination(int destination){
            this->destination = destination;
        }

        void moveAgent()
        {
            move(getSpeed() * cos(getAngle()), getSpeed() * sin(getAngle()));
        }

        void setDest(sf::CircleShape* dests)
        {
            if(nearest_tiles.size() < 2)
            {
                if(getPosition().x >= dests[getDestination()].getPosition().x)
                    setAngle(atan((getPosition().y - dests[getDestination()].getPosition().y)/(getPosition().x - dests[getDestination()].getPosition().x)) + M_PI);
                else
                    setAngle(atan((getPosition().y - dests[getDestination()].getPosition().y)/(getPosition().x - dests[getDestination()].getPosition().x)));
            }
            else
            {
                int i = rand() % nearest_tiles.size();
                if(getPosition().x >= nearest_tiles[i].getPosition().x)
                    setAngle(atan((getPosition().y - nearest_tiles[i].getPosition().y)/(getPosition().x - nearest_tiles[0].getPosition().x)) + M_PI);
                else
                    setAngle(atan((getPosition().y - nearest_tiles[i].getPosition().y)/(getPosition().x - nearest_tiles[0].getPosition().x)));
            }
        }

        void changeDest(sf::CircleShape* dests) 
        {
            if(sqrt(pow(getPosition().x - dests[getDestination()].getPosition().x, 2) + pow(getPosition().y - dests[getDestination()].getPosition().y, 2)) < 10)
            {
                int rand_dest;
                do{
                    rand_dest = rand() % dests_count;
                }while(rand_dest == getDestination());
                setDestination(rand_dest);
            }
        }

        void setNearestTiles(Tile** map, sf::CircleShape* dests)
        {
            nearest_tiles.clear();

            int x = (int)(getPosition().x/10);
            int y = (int)(getPosition().y/10);
            int x_min, x_max, y_min, y_max;

            if(x < 10) x_min = 0;
            else x_min = x-10;

            if(x > map_width-10) x_max = map_width;
            else x_max = x+10;

            if(y < 10) y_min = 0;
            else y_min = y-10;

            if(y > map_height-10) y_max = map_height;
            else y_max = y+10;


            for(int j = x_min; j < x_max; j++)
            {
                for(int k = y_min; k < y_max; k++)
                {

                    if(map[j][k].getFillColor() == Grey && distance(getPosition(), map[j][k].getCenterPosition()) < 10 && distance(getPosition(),dests[getDestination()].getPosition()) > distance(map[j][k].getCenterPosition(), dests[getDestination()].getPosition()))
                    {
                        nearest_tiles.push_back(map[j][k]);
                    }
                }
            }
        }
};

Agent* agentsInit(const sf::RenderWindow &App){
    static Agent agents[agents_count];
    for(int i = 0; i < agents_count; i++)
    {
        agents[i] = Agent(rand() % (int)(App.getSize().x - 2 * agents[i].getRadius()), rand() % (int)(App.getSize().y - 2 * agents[i].getRadius()),
                        rand() % dests_count, 3, rand() % 360);
    }
    return agents;
};

sf::CircleShape* destsInit(const sf::RenderWindow &App){
    static sf::CircleShape dests[dests_count];
    for(int i = 0; i < dests_count; i++)
    {
        dests[i] = sf::CircleShape(4);
        dests[i].setFillColor(sf::Color::Blue);
        dests[i].setPosition(App.getSize().x/2 +250*cos(2*M_PI*i/dests_count-M_PI/2), App.getSize().y/2 +250*sin(2*M_PI*i/dests_count-M_PI/2));
    }
    return dests;
};

class Destination: public sf::CircleShape{
    //TODO
};

void manageAgents(Agent* agents, Tile** map, sf::CircleShape* dests)
{
    for(int i = 0; i < agents_count; i++)
    {
        //setting nearest tiles
        agents[i].setNearestTiles(map, dests);

        //setting destination
        agents[i].setDest(dests);
        //destination reached
        agents[i].changeDest(dests);
        // agent movement
        agents[i].moveAgent();
    }
}

void drawObjects(sf::RenderWindow &App, Agent* agents, sf::CircleShape* dests)
{

    for(int i = 0; i < agents_count; i++)
    {  
        App.draw(agents[i]);
    }
    for(int i = 0; i < dests_count; i++)
    {
        App.draw(dests[i]);
    }

}

void stompGrass(Tile** map, Agent* agents){
    for(int i = 0; i < agents_count; i++)
    {
        int x = agents[i].getPosition().x/10;
        int y = agents[i].getPosition().y/10;
        map[x][y].stomp();
        // map[x][y].setFillColor(sf::Color(0, 255 - map[x][y].getGrassHeight(), 0));
    }
};
