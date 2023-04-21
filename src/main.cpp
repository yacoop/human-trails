#include "agent.hpp"
#include "map.hpp"


int main()
{
    // init random seed
    srand((unsigned)time(0));
    
    // init window
    sf::RenderWindow App(sf::VideoMode(800, 800), "Prosta animacja");
    App.setFramerateLimit(60);

    // init agents and destinations
    Agent* agents;
    agents = agentsInit(App);

    sf::CircleShape* dests;
    dests = destsInit(App);

    // init map
    Tile ** map;
    map = mapInit(App);

    // main loop
    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        App.clear();

        // draw map
        drawMap(App, map);

        //manage grass growth
        growGrass(map);

        stompGrass(map, agents);

        // manage agents movememt and destination
        manageAgents(agents, map, dests);

        //draw objects (agents and destinations)
        drawObjects(App, agents, dests);

        App.display();
    }

    return 0;
}