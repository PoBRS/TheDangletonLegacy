#ifndef _DEBUG
#define NDEBUG
#endif
#include <cassert>
#include "stdafx.h"
#include <vector>
#include "Actor.h"
#include <algorithm>
const float JUMP_VELOCITY = 15.f;
const float GRAVITATIONAL_ACCELERATION = 1.f;


const float MOVEMENT_ACCELERATION = 1.f;


Actor::Actor(void)
{
	this->clock = new clock_t();
	this->HitTimer();
	this->movementDeltaX = 0.f;
	this->movementDeltaY = 0.f;
	this->movementCalled = false;
	this->inAir = false;
	this->facingLeft = true;
}

Actor::~Actor(void)
{
	delete this->clock;
}
float Actor::getMovementDeltaY(void)
{
	return this->movementDeltaY;
}
float Actor::getMovementDeltaX(void)
{
	return this->movementDeltaX;
}
float Actor::GetSpeed(void)
{
	return this->maximumMovementSpeed;;
}

void Actor::SetSpeed(float _speed)
{
	this->maximumMovementSpeed = _speed;
}

bool Actor::IsInAir(void)
{
	return this->inAir;
}

/**
Fonction qui bouge l'acteur vers la gauche.
*/
void Actor::MoveLeft(void)
{
	this->movementDeltaX = std::max(-this->maximumMovementSpeed, this->movementDeltaX -  MOVEMENT_ACCELERATION);
	this->movementCalled = true;
	this->facingLeft = true;
}

/**
Fonction qui bouge l'acteur vers la droite.
*/
void Actor::MoveRight(void)
{
	this->movementDeltaX = std::min(this->maximumMovementSpeed, this->movementDeltaX +  MOVEMENT_ACCELERATION);
	this->movementCalled = true;
	this->facingLeft = false;
}

void Actor::SetPosition(float _positionX, float _positionY)
{
	this->setLeft(_positionX);
	this->setTop(_positionY);
	this->Trigger();
}



/**
Fonction qui permet de faire un saut.
Il va ajouter aux mouvement en Y du personnage la valeur d'un saut.
C'est la gravit� qui va permettre au joueur de revenir sur terre.
@See Gravity
*/
void Actor::Jump(void)
{
	if (!inAir)
	{
		this->movementDeltaY = -JUMP_VELOCITY;
		inAir = true;
	}
}

float Actor::getPositionX(void)
{
	return this->getLeft();
}

float Actor::getPositionY(void)
{
	return this->getTop();
}

/**
Fonction qui app�le le ralentissement de l'acteur si requis, de la gravit� et qui va updater la position de l'acteur.
@todo Mettre le stopMoving (this->movementCalled) dans un listener. Il sera appeler si aucunne interction du joueur est fait.
Ou encore, l'appeler lors des keyrealease. � discuter.
@see stopMoving()
@see gravitationalAttraction()
@see applyCharacterPosition

*/

void Actor::UpdatePosition(void)
{
	if (this->movementCalled == false)
	{
		this->stopMoving();
	}
	this->gravitationalAttraction();
	this->CheckCollision();
	this->applyCharacterPosition();

	this->movementCalled = false; //Reset the "listener".
}

/**
Fonction qui attire le joueur vers le bas.
*/
void Actor::gravitationalAttraction(void)
{
	this->movementDeltaY += GRAVITATIONAL_ACCELERATION;
}
/**
Fonction qui va ralentir le d�placement horizontal du joueur jusqu'� l'arr�t total.
*/
void Actor::stopMoving(void)
{
	if (this->movementDeltaX > 0.f)
	{
		this->movementDeltaX = std::max(0.f, this->movementDeltaX - MOVEMENT_ACCELERATION);
	}
	else if (this->movementDeltaX < 0.f)
	{
		this->movementDeltaX = std::min(0.f, this->movementDeltaX + MOVEMENT_ACCELERATION);
	}
}
/**
Fonction qui va changer la position de l'acteur en fonction de ses Deltas.
*/
void Actor::applyCharacterPosition(void)
{
	this->setLeft(this->getLeft() + this->movementDeltaX);

	this->setTop(this->getTop() + this->movementDeltaY);


	this->Trigger();
}

int Actor::GetNbLife(void)
{
	return this->nbLife;
}
void Actor::SetNbLife(int _nbLife)
{

	this->nbLife = _nbLife;
}

/**
Fonction qui prends les informations sur les cot� de contacte et les corriges si ceux-ci ne font pas de sense.
En particulier : Si aucun cot� n'est class� comme la direction de contacte, mais qu'il y a eu un contacte.
@param[in] _fromTop Si le contact vient du dessus.
@param[in] _fromLeft Si le contact vient du cot� gauche.
@param[in] _fromRight Si le contact vient du cot� droit.
@param[in] _fromBottom Si le contact vient du dessous.
@param[in] _otherCollisionBox Le collisionBox avec lequel on entre en contacte.
@param[out] _fromTop Si le contact vient du dessus(corrig�).
@param[out] _fromLeft Si le contact vient du cot� gauche(corrig�).
@param[out] _fromRight Si le contact vient du cot� droit(corrig�).
@param[out] _fromBottom Si le contact vient du dessous(corrig�).
*/
void Actor::correctSideOfContact(bool& _fromTop, bool& _fromLeft, bool& _fromRight, bool& _fromBottom, const CollisionBox& _otherCollisionBox) const
{

	float distanceCenterX = this->getCenterX() - _otherCollisionBox.getCenterX();
	float distanceCenterY = this->getCenterY() - _otherCollisionBox.getCenterY();

	if (std::abs(distanceCenterX) > std::abs(distanceCenterY)) // Then is mostly horizontal.
	{
		if (distanceCenterX <= 0)
		{
			_fromLeft = true;
		}
		else if (this->getBottom() + movementDeltaY != _otherCollisionBox.getTop()) 
		{
			_fromRight = true;
		}
	}
	else // Mostly horizontal
	{
		if (distanceCenterY <= 0)
		{
			_fromTop = true;
		}
		else if (std::abs(distanceCenterX) - this->getWidth()/2 <= _otherCollisionBox.getWidth()/2)
		{
			_fromBottom = true;
		}

	}
}

/**
Fonction qui retourne le sens que l'acteur fait face.
Elle retourne en fait si la derni�re appel a �t� MoveLeft ou MoveRight.
@return true si face � gauche, sinon false.
@see MoveLeft
@see MoveRight
*/
bool Actor::IsFacingLeft(void)
{
	return this->facingLeft;
}
bool Actor::Attack(void)
{

	bool attackSuccesful = false;

	if(this->GetNbLife() > 0)
	{
		this->SetNbLife(this->GetNbLife() - 1);

	}
	if(this->GetNbLife() <= 0)
	{
		this->SetNbLife(0);
		attackSuccesful = true;
	}
	return attackSuccesful;
}

void Actor::HitTimer(void)
{
	*(this->clock) = std::clock();
}

double Actor::timeSinceLastHit(void)
{
	clock_t endTime = std::clock();
	clock_t clockTicksTaken = endTime - *(this->clock);
	double timeInSeconds = clockTicksTaken / (double) CLOCKS_PER_SEC;
	return timeInSeconds;
}

void Actor::setMovementDeltaX(float _newDeltaX)
{
	this->movementDeltaX = _newDeltaX;
}
void Actor::setMovementDeltaY(float _newDeltaY)
{
	this->movementDeltaY = _newDeltaY;
}

void Actor::setFacingLeft(bool _facingLeft)
{
	this->facingLeft = _facingLeft;
}
void Actor::setInAir(bool _isInAir)
{
	this->inAir = _isInAir;
}