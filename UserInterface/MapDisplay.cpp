#include "MapDisplay.h"
#include <string>

MapDisplay::MapDisplay(std::string _filePath, MapTile&_linkedMapTile)
{
	
	if(_linkedMapTile.getTileValueX() != -1 || _linkedMapTile.getTileValueY() != -1)
	{


		if (!this->texture.loadFromFile("Ressources/TILESET.png"))
		{

		}
		else
		{
			this->sprite.setTexture(texture);
			
			this->sprite.setTextureRect(sf::IntRect(_linkedMapTile.getTileValueX() * 50.f, _linkedMapTile.getTileValueY() * 50.f, 50.f , 50.f));
			this->sprite.setPosition(_linkedMapTile.getPositionX() * 50.f, 50.f + (_linkedMapTile.getPositionY() * 50.f));
		}
	}

}
MapDisplay::~MapDisplay(void)
{
	
}

sf::Sprite MapDisplay::getSprite(void)
{
	return this->sprite;
}