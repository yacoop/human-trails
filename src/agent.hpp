#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>

#define agents_count 5000
#define dests_count 8

class Agent: public sf::CircleShape{
    private:
    float speed;
    float angle;
    int destination;

    public:
        Agent(float x = 0, float y = 0, int dest = 0, float speed = 1, float angle = 0,
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
            if(getPosition().x >= dests[getDestination()].getPosition().x)
                    setAngle(atan((getPosition().y - dests[getDestination()].getPosition().y)/(getPosition().x - dests[getDestination()].getPosition().x)) + M_PI);
                else
                    setAngle(atan((getPosition().y - dests[getDestination()].getPosition().y)/(getPosition().x - dests[getDestination()].getPosition().x)));
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
        dests[i].setFillColor(sf::Color::Green);
        dests[i].setPosition(App.getSize().x/2 +250*cos(2*M_PI*i/dests_count-M_PI/2), App.getSize().y/2 +250*sin(2*M_PI*i/dests_count-M_PI/2));
    }
    return dests;
};

class Destination: public sf::CircleShape{
    //TODO
};

void manageAgents(Agent* agents, sf::CircleShape* dests)
{
    for(int i = 0; i < agents_count; i++)
    {
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
    App.clear();
    for(int i = 0; i < agents_count; i++)
    {  
        App.draw(agents[i]);
    }
    for(int i = 0; i < dests_count; i++)
    {
        App.draw(dests[i]);
    }
    App.display();
}
