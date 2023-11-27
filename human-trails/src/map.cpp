#include "map.h"

//inits
void Map::MapInit(int width, int height) {
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            mTiles.push_back(Tile(i * Tile::sWidth, j * Tile::sHeight, dirt));
        }
    }
}

void Map::MapInit() {
    sf::Image image;

    if (!image.loadFromFile(GetPath("map.png")))
    {
        MapInit(80, 80);
    }
    else
    {
        int width = image.getSize().x;
        int height = image.getSize().y;
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                sf::Color color = image.getPixel(i, j);
                if (color.r == sf::Color::Black.r)
                    mTiles.push_back(Tile(i * Tile::sWidth, j * Tile::sHeight, pavement));
                else
                    mTiles.push_back(Tile(i * Tile::sWidth, j * Tile::sHeight, dirt));
            }
        }
    }
}

void Map::DestInit() {
    mDests.push_back(Dest(30 * Tile::sWidth, 14 * Tile::sHeight)); //mini
    //mDests.push_back(Dest(0.38 * WINDOW_WIDTH, 0.18 * WINDOW_HEIGHT)); //mini
    mDests.push_back(Dest(22 * Tile::sWidth, 40 * Tile::sHeight)); //fizyka
    mDests.push_back(Dest(8 * Tile::sWidth, 60 * Tile::sHeight)); //wibhis
    mDests.push_back(Dest(36 * Tile::sWidth, 64 * Tile::sHeight)); //mechanika
    mDests.push_back(Dest(60 * Tile::sWidth, 35 * Tile::sHeight)); //chemia
    mDests.push_back(Dest(74 * Tile::sWidth, 62 * Tile::sHeight)); //gg
}

void Map::AgentInit(int size) {
    for (int i = 0; i < size; i++)
    {
        mAgents.push_back(Agent());
    }
}

//loop methods
void Map::GrowGrass() {
    for (Tile& tile : mTiles)
    {
        if(tile.state == pavement)
            tile.setFillColor(Grey);
		else if (tile.GetGrassHeight() < 2) //state == dirt
        {
			tile.setFillColor(Brown);
			tile.Grow();
		}
		else
			tile.setFillColor(Green);
	}
}

void Map::Manage()
{
    for (Agent& agent : mAgents)
    {
        GetTile(agent)->Stomp();
        //setting nearest tiles
        SetNearestTiles(agent);
        //setting destination
        agent.SetDirection(mDests);
        // destination reached
        agent.ChangeDest(mDests);
        // agent movement
        agent.MoveAgent();
    }
}

void Map::Draw(sf::RenderWindow& window) {
    for (Tile& tile : mTiles)
    {
		window.draw(tile);
	}
    for (Dest& dest : mDests)
    {
		window.draw(dest);
	}
    for (Agent& agent : mAgents)
    {
		window.draw(agent);
	}
}

//getters
Tile* Map::GetTile(Agent& agent){
    int x, y;
    x = floor(agent.GetCenterPosition().x / Tile::sWidth);
    y = floor(agent.GetCenterPosition().y / Tile::sHeight);
    return &(mTiles[y*Map::sWidth+x]);
}

void Map::SetNearestTiles(Agent& agent)
{
    agent.mNearestTiles.clear();

    // jako funkcja?
    int x = (int)(agent.GetCenterPosition().x / Tile::sWidth);
    int y = (int)(agent.GetCenterPosition().y / Tile::sHeight);
    int x_min, x_max, y_min, y_max;

    //setting iteration range
    if (x < 10) x_min = 0;
    else x_min = x - 10;

    if (x > (Map::sWidth - 10)) x_max = Map::sWidth;
    else x_max = x + 10;

    if (y < 10) y_min = 0;
    else y_min = y - 10;

    if (y > (Map::sHeight - 10)) y_max = Map::sHeight;
    else y_max = y + 10;



    for (int k = y_min; k < y_max; k++)
        for (int j = x_min; j < x_max; j++)
        {
            if (agent.canNearestTiles(Map::mTiles[k * Map::sWidth + j], mDests))
            {
                agent.mNearestTiles.push_back(Map::mTiles[k * Map::sWidth + j]);
            }
        }
}
