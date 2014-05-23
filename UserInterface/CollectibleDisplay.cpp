#include "CollectibleDisplay.h"

CollectibleDisplay::CollectibleDisplay(void)
{
	
	if (!this->texture.loadFromFile("Ressources/coin.png"))
	{

	}
	else
	{

		this->sprite.setTexture(texture);
		this->sprite.setPosition(400.f, 200.f);
	
	}
}

CollectibleDisplay::~CollectibleDisplay(void)
{

}
Actor* CollectibleDisplay::GetCollectible(void)
{
	return this->collectible;
}

void CollectibleDisplay::SetCollectible(Actor* _collectible)
{
	this->collectible = _collectible;
}

void CollectibleDisplay::SetSpritePosition(void)
{
		
	float newX = this->collectible->getPositionX();
	float newY = this->collectible->getPositionY();
	this->sprite.setPosition(newX, newY);	
	

}
void CollectibleDisplay::Notify(void)
{
	this->SetSpritePosition();
}
sf::Sprite CollectibleDisplay::GetSprite(void)
{
	return this->sprite;
}
