#include "agent.hpp"
#include "map.hpp"

int main()
{
    // init random seed
    srand((unsigned)time(0));
    
    // init window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "human-trails");
    App.setFramerateLimit(60);

    // init agents and destinations
    Agent* agents = Agent::init();

    Dest* dests = Dest::init();

    // init map
    Tile** map = Tile::mapInit();

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
        Tile::drawMap(App, map);
        
        // manage grass growth
        Tile::growGrass(map);

        // all things that agents do
        Agent::manage(agents, map, dests);

        // draw objects (agents and destinations)
        drawObjects(App, agents, dests);

        App.display();
    }

    std::cout << Tile::tileCount << std::endl;
    std::cout << Agent::agentCount << std::endl;
    delete[] agents;
    delete[] dests;
    
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}