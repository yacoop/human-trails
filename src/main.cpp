#include "agent.hpp"

int main()
{
    // init random seed
    srand((unsigned)time(0));
    
    // init window
    sf::RenderWindow App(sf::VideoMode(800, 600), "Prosta animacja");
    App.setFramerateLimit(60);

    // init agents and destinations
    Agent* agents;
    agents = agentsInit(App);

    sf::CircleShape* dests;
    dests = destsInit(App);

    // main loop
    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        //manage agents movememt and destination
        manageAgents(agents, dests);

        //draw objects (agents and destinations)
        drawObjects(App, agents, dests);
    }

    return 0;
}