#include "stdafx.h"
#include "Player.h"
#include "SceneEntities.h"

const float WEAPON_RANGE = 20.f;
const unsigned int NB_LIFE_DEFAULT = 5;

Player::Player(void)
{

	this->SetNbLife(NB_LIFE_DEFAULT);
	this->SetPoints(0);

}

Player::~Player(void)
{

}

void Player::CheckCollision(void)
{
	for (std::map<CollisionBox*,EnumEntities>::const_iterator it = SceneEntities::getInstance().getEntitiesMap()->begin();it != SceneEntities::getInstance().getEntitiesMap()->end(); std::advance(it, 1))
	{
		if (std::abs(it->first->getLeft() - this->getLeft()) < 100 && std::abs(it->first->getTop() - this->getTop()) < 100)
		{
			if (((CollisionBox*)this)->IntersectWith(*it->first,this->getMovementDeltaX(), this->getMovementDeltaY()))
			{
				if (it->second == EnumEntities::ENDFLAG)
				{
					if (((Actor*)it->first)->Attack()) //Kill the flag to force the end of the Level.
					{
						return;
					}
				}

				if (it->second == EnumEntities::COLLECTIBLE)
				{
					if(((Actor*)it->first)->Attack()) // Kill the collectible.
					{
						SceneEntities::getInstance().getEntitiesMap()->erase(SceneEntities::getInstance().getEntitiesMap()->find(it->first));
						return;
					}
				}

				bool top = false;
				bool left = false;
				bool right = false;
				bool bottom = false;

				this->correctSideOfContact(top, left, right, bottom, *it->first);


				if (top)
				{

					if(it->second == EnumEntities::WALL)
					{
						this->setMovementDeltaY(0.f);
						this->setInAir(false);
					}
				}

				if (left)
				{
					//std::cout << "left"  << endl;
					this->setMovementDeltaX(0);
					if(it->second == EnumEntities::ENEMY)
					{

						if(this->timeSinceLastHit() > 2.00)
						{
							this->Attack();
							this->HitTimer();
							this->setMovementDeltaY(-10);
						}

					}

				}

				if (right)
				{
						this->setMovementDeltaX(0);
						if(it->second == EnumEntities::ENEMY)
						{
							if(this->timeSinceLastHit() > 2.00)
							{
								this->Attack();
								this->HitTimer();
								this->setMovementDeltaY(-10);
							}
						}

				}

				if (bottom)
				{
					if(it->second == EnumEntities::WALL )
					{
						this->setMovementDeltaY(0);
					}
				}
			}
		}
	}
}

void Player::SetPoints(int _points)
{
	this->points = _points;
}
int Player::GetPoints(void)
{
	return this->points;
}

