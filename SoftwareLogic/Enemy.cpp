#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(void)
{

}
Enemy::~Enemy(void)
{

}
void Enemy::CheckCollision(void)
{
	for (std::map<CollisionBox*,EnumEntities>::const_iterator it = SceneEntities::getInstance().getEntitiesMap()->begin();it != SceneEntities::getInstance().getEntitiesMap()->end(); std::advance(it, 1))
	{
		if (std::abs(it->first->getLeft() - this->getLeft()) < 100 && std::abs(it->first->getTop() - this->getTop()) < 100)
		{
			if (((CollisionBox*)this)->IntersectWith(*it->first,this->getMovementDeltaX(), this->getMovementDeltaY()))
			{

				bool top = false;
				bool left = false;
				bool right = false;
				bool bottom = false;

				this->correctSideOfContact(top, left, right, bottom, *it->first);

				if (top)
				{
					this->setMovementDeltaY(0);
				}

				if (left)
				{
					if(it->second == EnumEntities::WALL || it->second == EnumEntities::PLAYER)
					{
						this->setMovementDeltaX(0);
						this->SetSpeed(-this->GetSpeed());
						this->setFacingLeft(true);
					}
				}

				if (right)
				{
					if(it->second == EnumEntities::WALL || it->second == EnumEntities::PLAYER)
					{
						this->setMovementDeltaX(0);
						this->SetSpeed(-this->GetSpeed());
						this->setFacingLeft(false);
					}
				}

				if (bottom)
				{
					if(it->second == EnumEntities::PLAYER)
					{

						if(this->Attack())
						{
							SceneEntities::getInstance().getEntitiesMap()->erase(SceneEntities::getInstance().getEntitiesMap()->find(this));

							break;
						}
					}
					this->setMovementDeltaY(0);;
				}
			}
		}
	}

}
