#include "EnemyDisplay.h"

EnemyDisplay::EnemyDisplay(void)
{

	
	if (!this->texture.loadFromFile("Ressources/enemy.png"))
	{

	}
	else
	{

		this->sprite.setTexture(texture);
		this->sprite.setTextureRect(sf::IntRect(98, 110, 20, 20));
		this->SetLeftSprite();
		this->SetRightSprite();
		this->sprite.setPosition(400.f, 300.f);
		animationFrame = 0;
		this->moveLeft = true;
	}
}

bool EnemyDisplay::GetMoveLeft(void)
{
	return this->moveLeft;
}

void EnemyDisplay::SetMoveLeft(bool _moveLeft)
{
	this->moveLeft = _moveLeft;
}

EnemyDisplay::~EnemyDisplay(void)
{
	
	for(unsigned int i = 0 ; i < vectorLeftSprite.size(); i ++)
	{
		delete vectorLeftSprite[i];
	}
	for(unsigned int i = 0 ; i < vectorRightSprite.size(); i ++)
	{
		delete vectorRightSprite[i];
	}
	
}

void EnemyDisplay::Move(void)
{
	
	float newX = this->enemy->getPositionX();
	float newY = this->enemy->getPositionY();
	this->sprite.setPosition(newX, newY);

}

sf::Sprite EnemyDisplay::GetSprite(void)
{
	return this->sprite;
}


void EnemyDisplay::SetEnemy(Enemy* _enemy)
{
	this->enemy = _enemy;
}
void EnemyDisplay::Notify(void)
{
	this->Move();
}

sf::FloatRect EnemyDisplay::getBoundingRect(void) const
{
	sf::Transform toRectangle;
	sf::FloatRect rectangleBoundaries = toRectangle.transformRect(sprite.getGlobalBounds());
	return rectangleBoundaries;
}

void EnemyDisplay::MoveRight(void)
{
		
	
	if(animationFrame == 10)
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
void EnemyDisplay::ResetAnimationFrame(int _frame)
{
	animationFrame = _frame;
	itMoveLeft = vectorLeftSprite.begin();
	itMoveRight = vectorRightSprite.begin();
}
void EnemyDisplay::MoveLeft(void)
{
	
	if(this->animationFrame == 10)
	{
	
		itMoveLeft = vectorLeftSprite.begin();
		
		animationFrame = 0;
	
	}
	else if (this->animationFrame % 5 == 0)
	{
		
		itMoveLeft++;
		
	}
	this->animationFrame++;
	
	this->sprite = **itMoveLeft;

}

void EnemyDisplay::SetRightSprite(void)
{
	
	sf::Sprite * spriteRight = new sf::Sprite();;
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(98, 45, 20, 20));
	vectorRightSprite.push_back(spriteRight);
	
	spriteRight = new sf::Sprite();
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(120, 45, 20, 20));
    vectorRightSprite.push_back(spriteRight);
	
	
	spriteRight = new sf::Sprite();
	*spriteRight = sprite;
	spriteRight->setTextureRect(sf::IntRect(98, 45, 20, 20));
	vectorRightSprite.push_back(spriteRight);
	
	

	
	itMoveRight = vectorRightSprite.begin();

}

void EnemyDisplay::SetLeftSprite(void)
{

	sf::Sprite * spriteLeft = new sf::Sprite();;
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(98, 110, 20, 20));
	vectorLeftSprite.push_back(spriteLeft);
	
	spriteLeft = new sf::Sprite();
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(120, 110, 20, 20));
    vectorLeftSprite.push_back(spriteLeft);
	
	
	spriteLeft = new sf::Sprite();
	*spriteLeft = sprite;
	spriteLeft->setTextureRect(sf::IntRect(98, 110, 20, 20));
	vectorLeftSprite.push_back(spriteLeft);


	itMoveLeft = vectorLeftSprite.begin();
}

Actor* EnemyDisplay::GetEnemy(void)
{
	return this->enemy;
}