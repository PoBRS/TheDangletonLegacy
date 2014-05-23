#include "WeaponDisplay.h"
WeaponDisplay::WeaponDisplay(void)
{
	if (!this->texture.loadFromFile("Ressources/sword.png"))
	{

	}
	else
	{
		this->sprite.setTexture(texture);
		this->sprite.setPosition(200.f, 200.f);
	
	}
}

WeaponDisplay::~WeaponDisplay(void)
{

}
sf::Sprite WeaponDisplay::GetSprite(void)
{
	return this->sprite;
}

void WeaponDisplay::SetPosition(float _x, float _y)
{
	this->sprite.setPosition(_x, _y);
}
void WeaponDisplay::Notify(void)
{
	this->sprite.rotate(10);
}