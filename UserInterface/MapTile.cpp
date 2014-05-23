////http://www.sfml-dev.org/tutorials/2.0/graphics-vertex-array.php
#include "MapTile.h"


MapTile::MapTile(void)
{
	this->tileValueX = 0;
	this->tileValueY = 0;
	this->positionX = 0;
	this->positionY = 0;

}

MapTile::~MapTile(void)
{

}

void MapTile::AssignValue(int _valueX, int _valueY)
{
	this->tileValueX = _valueX;
	this->tileValueY = _valueY;
}

void MapTile::AssignPosition(int _valueX, int _valueY)
{
	positionX = _valueX;
	positionY = _valueY;
	this->setLeft(positionX * 50);
	this->setTop(positionY * 50 + 50);
}

int MapTile::getTileValueX(void)
{
	return this->tileValueX;
}

int MapTile::getTileValueY(void)
{
	return this->tileValueY;
}

int MapTile::getPositionX(void)
{
	return this->positionX;
}

int MapTile::getPositionY(void)
{
	return this->positionY;
}