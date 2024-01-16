#include "map.h"

void Map::SetDirection(Agent& agent)
{
    double dy = agent.GetCenterPosition().y, dx = agent.GetCenterPosition().x;
    sf::Vector2f destCPos;

    if (agent.mNearestTiles.size() <= 1)
    {
        destCPos = mDests[agent.GetDestination()].GetCenterPosition();
        dy -= destCPos.y;
        dx -= destCPos.x;
        if (agent.GetCenterPosition().x >= destCPos.x)
            agent.SetAngle(atan(dy / dx) + M_PI);
        
        else
            agent.SetAngle(atan(dy / dx));
    }
    else
    {
        int i = rand() % agent.mNearestTiles.size();

        destCPos = agent.mNearestTiles[i].GetCenterPosition();
        dy -= agent.mNearestTiles[i].GetCenterPosition().y;
        dx -= agent.mNearestTiles[i].GetCenterPosition().x;

        if (agent.GetCenterPosition().x >= destCPos.x)
            agent.SetAngle(atan(dy / dx) + M_PI);
        else
            agent.SetAngle(atan(dy / dx));
    }

    sf::Vector2f nextPos = agent.GetCenterPosition() + agent.GetSpeed() * sf::Vector2f(cos(agent.GetAngle()) , sin(agent.GetAngle()));
    double angle;
    while (mTiles[(int)floor(nextPos.y / Tile::sHeight) * Map::sWidth + (int)floor(nextPos.x / Tile::sWidth)].state == obstacle)
    {
        angle = rand() % 2 == 1 ? (double)rand() / RAND_MAX * 20 / 180 * M_PI : -(double)rand() / RAND_MAX * 20 / 180 * M_PI;
		agent.SetAngle(agent.GetAngle() + angle);
        nextPos = agent.GetCenterPosition() + agent.GetSpeed() * sf::Vector2f(cos(agent.GetAngle()), sin(agent.GetAngle()));
	}
}

//inits
void Map::MapInit(int width, int height) {
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            mTiles.push_back({ i * Tile::sWidth, j * Tile::sHeight, dirt });
        }
    }
}

void Map::MapInit() {
    sf::Image image;

    if (!image.loadFromFile(MAP_PATH))
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
                if (color.r == sf::Color::Red.r && color.g == sf::Color::Red.g && color.b == sf::Color::Red.b)
                    mTiles.push_back({ i * Tile::sWidth, j * Tile::sHeight, obstacle });
                else if (color.r == sf::Color::Blue.r && color.g == sf::Color::Blue.g && color.b == sf::Color::Blue.b)
                    mTiles.push_back({ i * Tile::sWidth, j * Tile::sHeight, pavement });
                else
                    mTiles.push_back({ i * Tile::sWidth, j * Tile::sHeight, dirt });
            }
        }
    }
}

void Map::DestInit() {
    mDests.push_back({ 31 * Tile::sWidth, 10 * Tile::sHeight }); //mini
    mDests.push_back({ 21 * Tile::sWidth, 36 * Tile::sHeight }); //fizyka
    mDests.push_back({ 5 * Tile::sWidth, 59 * Tile::sHeight }); //wibhis
    mDests.push_back({ 36 * Tile::sWidth, 62 * Tile::sHeight }); //mechanika
    mDests.push_back({ 51 * Tile::sWidth, 31 * Tile::sHeight }); //chemia
    mDests.push_back({ 76 * Tile::sWidth, 62 * Tile::sHeight }); //gg
}

void Map::AgentInit(int size) {
    int r;
    for (int i = 0; i < size; i++)
    {
        r = rand() % mDests.size();
        mAgents.push_back({ mDests[r].GetCenterPosition(), r });
    }
}

void Map::GrowGrass() {
    for (Tile& tile : mTiles)
    {
        if (tile.state == dirt) {
            if (tile.GetGrassHeight() < 2)
            {
                tile.setFillColor(Brown);
                tile.Grow();
            }
            else
                tile.setFillColor(Green);
        }
	}
}

void Map::Manage()
{
    for (Agent& agent : mAgents)
    {
        GetTile(agent)->Stomp();
        //setting nearest tiles
        SetNearestTiles(agent);
        //setting direction to destination
        SetDirection(agent);
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
    x = (int) floor(agent.GetCenterPosition().x / Tile::sWidth);
    y = (int) floor(agent.GetCenterPosition().y / Tile::sHeight);
    return &(mTiles[y*Map::sWidth+x]);
}

void Map::SetNearestTiles(Agent& agent)
{
    agent.mNearestTiles.clear();
 
    int x = (int) floor(agent.GetCenterPosition().x / Tile::sWidth);
    int y = (int) floor(agent.GetCenterPosition().y / Tile::sHeight);
    int x_min, x_max, y_min, y_max;

    //setting iteration range
    x_min = x < searchDist ? 0 : x - searchDist;
    x_max = x > (Map::sWidth - searchDist) ? Map::sWidth : x + searchDist;

    y_min = y < searchDist ? 0 : y - searchDist;
    y_max = y > (Map::sHeight - searchDist) ? Map::sHeight : y + searchDist;

    for (int k = y_min; k < y_max; k++)
        for (int j = x_min; j < x_max; j++)
        {
            if (agent.canNearestTiles(Map::mTiles[k * Map::sWidth + j], mDests))
            {
                agent.mNearestTiles.push_back(Map::mTiles[k * Map::sWidth + j]);
                //Map::mTiles[k * Map::sWidth + j].setFillColor(sf::Color::Cyan);
            }
        }
}
