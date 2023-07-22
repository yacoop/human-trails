#include "agent.h"
#include "map.h"



int main()
{
    // init random seed
    srand((unsigned)time(0));

    // init window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "human-trails");
    App.setFramerateLimit(60);

    Map map;

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

        map.GrowGrass();


        map.Manage();

        map.Draw(App);
        App.display();
    }

    return 0;
}