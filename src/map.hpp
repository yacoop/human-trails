#pragma once

#include "agent.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>

const int map_width =  80;
const int map_height = 80;

sf::Color Grey = sf::Color(128, 128, 128);;

class Tile: public sf::RectangleShape{
    private:
        float grass_height;
        double lambda = 0.9;

    public:
        Tile(float x = 0, float y = 0, float grass_height = 0){
            RectangleShape();
            setSize(sf::Vector2f(10, 10));
            setFillColor(Grey);
            setPosition(x, y);
            this->grass_height = 1;
        }

        sf::Vector2f getCenterPosition(){
            return getPosition()+getSize()*.5f;
        }

        float getGrassHeight(){
            return grass_height;
        }

        void setGrassHeight(float grass_height){
            this->grass_height = grass_height;
        }

        void grow(){
            setGrassHeight(getGrassHeight()+0.01);
        }

        void stomp(){
            setGrassHeight(getGrassHeight()*lambda);
        }
};

Tile** mapInit(sf::RenderWindow &App){
    static Tile** map = new Tile*[map_width];
    for(int i = 0; i < map_width; i++)
    {
        map[i] = new Tile[map_height];
        for(int j = 0; j < map_height; j++)
        {
            map[i][j] = Tile((double)i*800/(double)map_width, j*800/(double)map_height, 0);
        }
    }
    return map;
};

void growGrass(Tile** map){
    for(int i = 0; i < map_width; i++)
    {
        for(int j = 0; j < map_height; j++)
        {
            if(map[i][j].getGrassHeight() < 2) 
            {
                map[i][j].setFillColor(Grey);
                map[i][j].grow();
            }
            else map[i][j].setFillColor(sf::Color::Green);
        }
    }
};

void drawMap(sf::RenderWindow &App, Tile** map){
    for(int i = 0; i < map_width; i++)
    {
        for(int j = 0; j < map_height; j++)
        {
            App.draw(map[i][j]);
        }
    }
};

double distance(sf::Vector2f v1, sf::Vector2f v2){
    return sqrt(pow(v1.x-v2.x, 2) + pow(v1.y-v2.y, 2));
};

