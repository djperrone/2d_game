#pragma once
#include <string>
class Map
{
public:
	//map file path, map scale, tileseize
	//tID = txture id
	Map(const char* mpf, int ms, int ts);
	~Map();

	void LoadMap(std::string path, int sizeX, int sizeY);
	void AddTile(int srcX, int srcY, int xpos, int ypos);

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
	int scaledSize;
};