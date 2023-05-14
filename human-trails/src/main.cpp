#include "agent.hpp"
#include "map.hpp"


int main()
{
    // init random seed
    srand((unsigned)time(0));

    // init window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "human-trails");
    App.setFramerateLimit(60);

    std::vector<Agent> agents;
    Agent::Init(agents, AGENTS_COUNT);

    //Agent* agents = Agent::Init();

    Dest* dests = Dest::Init();

    std::cout << agents.size() << std::endl;
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


        Tile::DrawMap(App, map);
        Tile::GrowGrass(map);
        Agent::Manage(agents, map, dests);

        DrawObjects(App, agents, dests);

        App.display();
    }


    std::cout << Agent::sAgentCount << std::endl;
    std::cout << Agent::sAgentCopied << std::endl;
    std::cout << Tile::sTileCount << std::endl;
    std::cout << Tile::sTileCopied << std::endl;

    delete[] dests;

    for (int i = 0; i < MAP_WIDTH; i++)
    {
        delete[] map[i];
    }
    delete[] map;



    return 0;
}