#include "agent.hpp"
#include "map.hpp"



int main()
{
    // init random seed
    srand((unsigned)time(0));
    
    // init window
    sf::RenderWindow App(sf::VideoMode(window_width, window_height), "human-trails");
    App.setFramerateLimit(60);

    // init agents and destinations
    Agent* agents;
    agents = agentsInit();

    sf::CircleShape* dests;
    dests = destsInit();

    // init map
    Tile ** map;
    map = mapInit();

    // sf::CircleShape** circle = new sf::CircleShape*[map_width];
    // for(int i = 0; i < map_width; i++)
    // {
    //     circle[i] = new sf::CircleShape[map_height];
    //     for(int j = 0; j < map_height; j++)
    //     {
    //         circle[i][j] = sf::CircleShape(2);
    //         circle[i][j].setPosition(map[i][j].getCenterPosition() - sf::Vector2f(2,2));
    //     }
    // }

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