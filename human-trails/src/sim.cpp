#include "sim.h"
#include <fstream>

void Sim::Run()
{
    // init random seed
    srand((unsigned)time(0));

    // init window
    this->win.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "human-trails");
    this->win.setFramerateLimit(0);

    Map map;

    int c = 0;

    // main loop
    while (this->win.isOpen() && c < 60*60*5)
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
        c++;
    }

    std::ofstream myfile("./out/density.txt");
    int x = 0;
    int y = 0;
    for (Tile& tile : map.mTiles)
    {
        if (x >= 80)
        {
			x = 0;
			y++;
		}
        myfile << x << " " << y << " " << tile.beenThere << std::endl;
        x++;
	}

}
