#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>

#define agents_count 500
#define dests_count 3

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

};

class Destination: public sf::CircleShape{
    //TODO
};

int main()
{
    sf::RenderWindow App(sf::VideoMode(800, 600), "Prosta animacja");
    App.setFramerateLimit(60);

    srand((unsigned)time(0));

    Agent agents[agents_count];
    for(int i = 0; i < agents_count; i++)
    {
        agents[i] = Agent(rand() % (int)(App.getSize().x - 2 * agents[i].getRadius()), rand() % (int)(App.getSize().y - 2 * agents[i].getRadius()),
                        rand() % dests_count, 3, rand() % 360);
    }

    sf::CircleShape dests[dests_count];
    for(int i = 0; i < dests_count; i++)
    {
        dests[i] = sf::CircleShape(4);
        dests[i].setFillColor(sf::Color::Green);
        dests[i].setPosition(App.getSize().x/2 +250*cos(2*M_PI*i/dests_count+M_PI/2), App.getSize().y/2 +250*sin(2*M_PI*i/dests_count+M_PI/2));
    }

    while (App.isOpen())
    {
        sf::Event event;
        while (App.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        for(int i = 0; i < agents_count; i++)
        {
            //setting destination
            if(agents[i].getPosition().x > dests[agents[i].getDestination()].getPosition().x)
                agents[i].setAngle(atan((agents[i].getPosition().y - dests[agents[i].getDestination()].getPosition().y)/(agents[i].getPosition().x - dests[agents[i].getDestination()].getPosition().x)) + M_PI);
            else
                agents[i].setAngle(atan((agents[i].getPosition().y - dests[agents[i].getDestination()].getPosition().y)/(agents[i].getPosition().x - dests[agents[i].getDestination()].getPosition().x)));

            //destination reached
            if(sqrt(pow(agents[i].getPosition().x - dests[agents[i].getDestination()].getPosition().x, 2) + pow(agents[i].getPosition().y - dests[agents[i].getDestination()].getPosition().y, 2)) < 10)
            {
                int rand_dest;
                do{
                    rand_dest = rand() % dests_count;
                }while(rand_dest == agents[i].getDestination());
                agents[i].setDestination(rand_dest);

            }

            // agent movement
            agents[i].move(agents[i].getSpeed() * cos(agents[i].getAngle()), agents[i].getSpeed() * sin(agents[i].getAngle()));

            // // agent collision with window borders
            // if (agents[i].getPosition().x + 2 * agents[i].getRadius() >= App.getSize().x || agents[i].getPosition().x <= 0)
            //     agents[i].setAngle(M_PI - agents[i].getAngle());
            // if (agents[i].getPosition().y + 2 * agents[i].getRadius() >= App.getSize().y || agents[i].getPosition().y <= 0)
            //     agents[i].setAngle(-agents[i].getAngle());
        }
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

    return 0;
}