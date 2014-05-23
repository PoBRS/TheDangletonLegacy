#include "Background.h"
#include <string>

Background::Background(std::string _filePath)
{

	if (!this->texture.loadFromFile(_filePath))
	{

	}
	else
	{
		this->sprite.setTexture(texture);


		this->sprite.setPosition(0, 100);
	}


}
Background::~Background(void)
{

}

sf::Sprite Background::getSprite(void)
{
	return this->sprite;
}