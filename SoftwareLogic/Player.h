#ifndef _PLAYER_H
#define _PLAYER_H

#include "Actor.h"

class Player: public Actor
{
public:
	Player(void);
	~Player(void);
	void SetPoints(int _points);
	void CheckCollision(void);
	int GetPoints(void);
private:
	int points;
};

#endif