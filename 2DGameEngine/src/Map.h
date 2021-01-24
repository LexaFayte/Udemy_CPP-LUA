#pragma once
#include <string>

class Map
{
public:
	Map(std::string textureId, int scale, int tileSize) :
		_textureId(textureId),
		_scale(scale),
		_tileSize(tileSize)
	{};

	~Map() {};

	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void AddTile(int sourceX, int sourceY, int posX, int posY);

private:
	std::string _textureId;
	int _scale;
	int _tileSize;

};