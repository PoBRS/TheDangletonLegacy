#include "Map.h"
#include <iostream>
#define MAXIMUM_MAP_WIDTH 200
#define MAXIMUM_MAP_HEIGHT 10
Map::Map(std::string _mapFilePath)
{
	BuildMapArray(_mapFilePath);
}

Map::~Map(void)
{

	for(unsigned int i = 0; i < mapDisplay.size(); i++)
	{
		delete mapDisplay[i];
	}

	
	for(unsigned int i = 0; i < mapTileVector.size(); i++)
	{
		delete mapTileVector[i];
	}



}



void Map::BuildMapArray(std::string _mapFilePath)
{
	reader = new TextFileReader();
	this->mapDispositionArray = reader->ReadInCharArray(_mapFilePath, MAXIMUM_MAP_WIDTH, MAXIMUM_MAP_HEIGHT);

	int compteur = 0;

	for (unsigned int column = 0; column < MAXIMUM_MAP_WIDTH; column++)
	{
		for (unsigned int line = 0; line < MAXIMUM_MAP_HEIGHT; line++)
		{
			if((int)this->mapDispositionArray[line][column] != 46)
			{
				if((int)this->mapDispositionArray[line][column] == 69)
				{
					this->SetEnemy(line, column);
				}
				else if((int)this->mapDispositionArray[line][column] == 67)
				{
					this->SetCollectible(line, column);
				}
				else if ((int)this->mapDispositionArray[line][column] == 70)
				{

				}
				else
				{
					MapTile *mapTile = (MapTile*)SceneEntities::getInstance().CreateEntity(EnumEntities::WALL);
					mapTile->setHeight(50.f);
					mapTile->setWidth(50.f);
					mapTile->AssignValue((int)this->mapDispositionArray[line][column] - 48,0);
					mapTile->AssignPosition(column,line);
					this->mapTileVector.push_back(mapTile);
				}
			}
			
			
		}
	}
	

	for(unsigned int i = 0; i < mapTileVector.size(); i++)
	{
		MapDisplay* displayedTile = new MapDisplay("../UserInterface/Ressources/TILEMAP.png",*mapTileVector[i]);
		mapDisplay.push_back(displayedTile);	
	}



	delete reader;
}

void Map::SetEnemy(int _x, int _y)
{
	this->positionXEnemy.push_back(_x);
	this->positionYEnemy.push_back(_y);
}

void Map::SetCollectible(int _x, int _y)
{
	this->positionXCollectible.push_back(_x);
	this->positionYCollectible.push_back(_y);
}

void Map::displayMap(sf::RenderWindow& _mWindow)
{

	float viewWidth = _mWindow.getView().getSize().x;
	float viewHeight = _mWindow.getView().getSize().y;
	float xPositionView = _mWindow.getView().getCenter().x;
	float yPositionView = _mWindow.getView().getCenter().y;
	for (std::vector<MapDisplay*>::const_iterator it=mapDisplay.begin(); it < mapDisplay.end(); it++)
	{
		if ((std::abs((*it)->getSprite().getPosition().x - xPositionView) < viewWidth/2.f + 50) && (std::abs((*it)->getSprite().getPosition().y - yPositionView) < viewHeight/2.f + 50))
		{
			_mWindow.draw((*it)->getSprite());
		}
	}
}
std::vector<int> Map::GetpositionXCollectible(void)
{
	return positionXCollectible;
}

std::vector<int> Map::GetpositionYCollectible(void)
{
	return positionYCollectible;
}

std::vector<int> Map::GetpositionXEnemy(void)
{
	return positionXEnemy;
}

std::vector<int> Map::GetpositionYEnemy(void)
{
	return positionYEnemy;
}
