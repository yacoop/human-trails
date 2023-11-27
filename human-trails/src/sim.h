#pragma once

#include "common.h"
#include "map.h"

class Sim {

public:
	void Run();

private:
	sf::RenderWindow win;
	Map map;

};