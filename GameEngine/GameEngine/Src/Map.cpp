#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/components.h"

//manager objext defined somewhere else
extern Manager manager;


Map::Map(const char* mpf, int ms, int ts) : mapFilePath(mpf), mapScale(ms), tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	std::string line;
	std::fstream mapFile;
	mapFile.open(path);
	char tile;
	char c;

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapFile.ignore();
		}
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize,tileSize);
				//mapFile.ignore();
				tcol.addGroup(Game::groupColliders);

			}
			mapFile.ignore();
		}
	}

	mapFile.close();

}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale,mapFilePath);
	tile.addGroup(Game::groupMap);
}




//#include "Map.h"
//#include "TextureManager.h"
//#include "Game.h"
//#include <fstream>
//
//
//Map::Map()
//{
//
//}
//
//Map::~Map()
//{
//
//}
//
//void Map::LoadMap(std::string path, int sizeX, int sizeY)
//{
//	std::string line;
//	std::fstream mapFile;
//	mapFile.open(path);
//	char tile;
//
//	for (int y = 0; y < sizeY; y++)
//	{
//		int x = 0;
//		std::getline(mapFile, line);
//		for (int i = 0; i < line.length(); i++)
//		{
//			if(line[i] == ' ' || line[i] == ',')
//			{
//				
//			}
//			else
//			{				
//				x++;
//				char tile = line[i];
//				Game::AddTile(atoi(&tile), x*32, y*32);
//				std::cout << tile << ", ";
//			}
//			
//
//		}
//		std::cout << std::endl;
//	}
//
//
//
//	//for (int y = 0; y < sizeY; y++)
//	//{
//	//	for (int x = 0; x < sizeX; x++)
//	//	{
//	//		mapFile.get(tile);
//	//		Game::AddTile(atoi(&tile), x * 32, y * 32);
//	//		mapFile.ignore();
//	//	}
//	//}
//
//	mapFile.close();
//
//}
//
