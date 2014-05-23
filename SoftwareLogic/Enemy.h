#ifndef _ENEMY_H
#define _ENEMY_H
#include "Actor.h"
class Enemy: public Actor
{
public:
	Enemy(void);
	~Enemy(void);
	void CheckCollision(void);

private:


};

#endif