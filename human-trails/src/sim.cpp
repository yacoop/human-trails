#include "sim.h"

void Sim::Run()
{
    // init random seed
    srand((unsigned)time(0));

    // init window
    this->win.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "human-trails");
    this->win.setFramerateLimit(60);

    Map map;

    // main loop
    while (this->win.isOpen())
    {
        sf::Event event;
        while (this->win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->win.close();
        }

        this->win.clear();

        map.GrowGrass();
        map.Manage();
        map.Draw(this->win);

        this->win.display();
    }
}
