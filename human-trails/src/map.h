#pragma once

#include "common.h"
#include "tile.h"
#include "dest.h"
#include "agent.h"


class Map
{
public:
	Map()
	{
		MapInit();
		DestInit();
		AgentInit(sAgentSize);
	}

	void GrowGrass();
	void Manage();
	void Draw(sf::RenderWindow& window);
	
	Tile* GetTile(Agent& agent);
	void SetNearestTiles(Agent& agent);

public:
	static const int sWidth = 80;
	static const int sHeight = 80;
	static const int sSize = sWidth * sHeight;
	static const int sDestSize = 6;
	static const int sAgentSize = 100;

	std::vector<Tile> mTiles;


private:
	void SetDirection(Agent& agent);
	void MapInit(int width, int height);
	void MapInit();
	void DestInit();
	void AgentInit(int size);

private:
	std::vector<Dest> mDests;
	std::vector<Agent> mAgents;
	int searchDist = 10;
	std::string MAP_PATH = GetPath("maps/realmyobst.png");
};