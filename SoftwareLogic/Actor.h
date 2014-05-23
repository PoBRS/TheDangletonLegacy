#ifndef _ACTOR_H
#define _ACTOR_H
#include "Observable.h"
#include "CollisionBox.h"
#include "SceneEntities.h"
#include <ctime>

class Actor : public Observable, public CollisionBox
{

public:
	Actor(void);
	~Actor(void);

	float GetSpeed(void);
	void SetSpeed(float speed);
	void MoveLeft(void);
	void MoveRight(void);
	void SetPosition(float _positionX, float _positionY);
	void Jump(void);
	float getPositionX(void);
	float getPositionY(void);
	void UpdatePosition(void);

	int GetNbLife(void);
	void SetNbLife(int _nbLife);
	virtual void CheckCollision(void){};
	bool IsFacingLeft(void);
	bool Attack(void);
	bool IsInAir(void);

protected:
	void setFacingLeft(bool _facingLeft);
	void setInAir(bool _isInAir);
	float getMovementDeltaX(void);
	float getMovementDeltaY(void);
	void setMovementDeltaX(float _newDeltaX);
	void setMovementDeltaY(float _newDeltaY);
	void HitTimer(void);
	double timeSinceLastHit(void);
	void correctSideOfContact(bool& _fromTop, bool& _fromLeft, bool& _fromRight, bool& _fromBottom, const CollisionBox& _otherCollisionBox) const;
private:
	bool facingLeft;
	bool inAir;
	void gravitationalAttraction(void);
	void applyCharacterPosition(void);
	void stopMoving(void);
	float movementDeltaY;
	float movementDeltaX;
	bool movementCalled; //a listener-like. It's to change.

	int nbLife;

	float maximumMovementSpeed;
	clock_t* clock;
};

#endif
