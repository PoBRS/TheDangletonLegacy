#include "EndFlagDisplay.h"

EndFlagDisplay::EndFlagDisplay(void)
{
	
	if (!this->texture.loadFromFile("Ressources/flag.png"))
	{

	}
	else
	{

		this->sprite.setTexture(texture);
		this->sprite.setPosition(4500.f, 350.f);
	
	}
}

EndFlagDisplay::~EndFlagDisplay(void)
{

}
Actor* EndFlagDisplay::GetEndFlag(void)
{
	return this->EndFlag;
}

void EndFlagDisplay::SetEndFlag(Actor* endFlag)
{
	this->EndFlag = endFlag;
}

void EndFlagDisplay::SetSpritePosition(void)
{
		
	float newX = this->EndFlag->getPositionX();
	float newY = this->EndFlag->getPositionY();
	this->sprite.setPosition(newX, newY);	
	

}
void EndFlagDisplay::Notify(void)
{
	this->SetSpritePosition();
}
sf::Sprite EndFlagDisplay::GetSprite(void)
{
	return this->sprite;
}
