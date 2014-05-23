#include "PlayerDisplay.h"

PlayerDisplay::PlayerDisplay(void)
{

	
	if (!this->texture.loadFromFile("Ressources/player.png"))
	{

	}
	else
	{
		
	
		this->weaponDisplay = new WeaponDisplay();
		this->sprite.setTexture(texture);
		this->sprite.setTextureRect(sf::IntRect(32, 64, 32, 32));
		this->SetLeftSprite();
		this->SetRightSprite();
		this->sprite.setPosition(200.f, 200.f);
		animationFrame = 0;
	}

}
PlayerDisplay::~PlayerDisplay(void)
{
	
	for(unsigned int i = 0 ; i < vectorLeftSprite.size(); i ++)
	{
		delete vectorLeftSprite[i];
	}
	for(unsigned int i = 0 ; i < vectorRightSprite.size(); i ++)
	{
		delete vectorRightSprite[i];
	}
	delete this->weaponDisplay;
	
}

sf::Sprite PlayerDisplay::GetWeapon(void)
{
	return this->weaponDisplay->GetSprite();
}

void PlayerDisplay::Move(void)
{
	float newX = this->player->getPositionX();
	float newY = this->player->getPositionY();
	this->weaponDisplay->SetPosition(newX + 10, newY - 5);
	this->sprite.setPosition(newX, newY);


}

sf::Sprite PlayerDisplay::GetSprite(void)
{
	return this->sprite;
}

void PlayerDisplay::SetPlayer(Actor* _player)
{
	this->player = _player;
	
}

void PlayerDisplay::Notify(void)
{
	this->Move();
}

sf::FloatRect PlayerDisplay::getBoundingRect(void) const
{
	sf::Transform toRectangle;
	sf::FloatRect rectangleBoundaries = toRectangle.transformRect(sprite.getGlobalBounds());
	return rectangleBoundaries;
}

void PlayerDisplay::MoveRight(void)
{
			
	if(animationFrame == 15)
	{
	
		itMoveRight = vectorRightSprite.begin();
		
		animationFrame = 0;
	
	}
	else if (animationFrame % 5 == 0)
	{
		
		itMoveRight++;
		
	}
	animationFrame++;
	
	this->sprite = **itMoveRight;


}
void PlayerDisplay::ResetAnimationFrame(int _frame)
{
	animationFrame = _frame;
	itMoveLeft = vectorLeftSprite.begin();
	itMoveRight = vectorRightSprite.begin();
}
void PlayerDisplay::MoveLeft(void)
{
	
	if(animationFrame == 15)
	{
	
		itMoveLeft = vectorLeftSprite.begin();
		
		animationFrame = 0;
	
	}
	else if (animationFrame % 5 == 0)
	{
		
		itMoveLeft++;
		
	}
	animationFrame++;
	
	this->sprite = **itMoveLeft;

}

void PlayerDisplay::SetRightSprite(void)
{
	
	sf::Sprite * spriteRight = new sf::Sprite();;
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(32, 64, 32, 32));
	vectorRightSprite.push_back(spriteRight);
	
	spriteRight = new sf::Sprite();
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(64, 64, 32, 32));
    vectorRightSprite.push_back(spriteRight);
	
	
	spriteRight = new sf::Sprite();
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(32, 64, 32, 32));
	vectorRightSprite.push_back(spriteRight);
	
	 
	spriteRight = new sf::Sprite();
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(0, 64, 32, 32));
	vectorRightSprite.push_back(spriteRight);

	
	itMoveRight = vectorRightSprite.begin();

}

void PlayerDisplay::SetLeftSprite(void)
{

	sf::Sprite * spriteLeft = new sf::Sprite();;
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(32, 32, 32, 32));
	vectorLeftSprite.push_back(spriteLeft);
	
	spriteLeft = new sf::Sprite();
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(64, 32, 32, 32));
    vectorLeftSprite.push_back(spriteLeft);
	
	
	spriteLeft = new sf::Sprite();
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(32, 32, 32, 32));
	vectorLeftSprite.push_back(spriteLeft);
	
	 
	spriteLeft = new sf::Sprite();
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(0, 32, 32, 32));
	vectorLeftSprite.push_back(spriteLeft);

	
	itMoveLeft = vectorLeftSprite.begin();
}