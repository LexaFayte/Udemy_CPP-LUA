#include "Map.h"
#include "Game.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"
#include <fstream>
#include "Constants.h"


void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
	std::fstream mapFile;
	mapFile.open(filePath);

	// #TODO_REFACTOR: can we make this better? Flatten the array? Tokenize by delimiter?
	for (int y = 0; y < mapSizeY; ++y)
	{
		for (int x = 0; x < mapSizeX; ++x)
		{
			char ch;
			mapFile.get(ch);
			int sourceRectY = atoi(&ch) * _tileSize;
			mapFile.get(ch);
			int sourceRectX = atoi(&ch) * _tileSize;
			AddTile(sourceRectX, sourceRectY, x * (_scale * _tileSize), y * (_scale * _tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int posX, int posY)
{
	Entity& newTile(Game::GetEntityManager().AddEntity("Tile", LayerType::TILEMAP));
	newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, posX, posY, _tileSize, _scale, _textureId);
}
