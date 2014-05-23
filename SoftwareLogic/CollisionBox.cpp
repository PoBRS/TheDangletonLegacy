#include "stdafx.h"
#include "CollisionBox.h"
#include <algorithm>





/**
Constructeur de CollisionBox
@param[in] _x Position en X du coté gauche. Defaut 0
@param[in] _y Position en Y du coté haut. Defaut 0
@param[in] _width Largeur de la boîte. Defaut 0
@param[in] _height Hauteur de la boîte. Defaut 0
*/
CollisionBox::CollisionBox(float _x, float _y, float _width, float _height)
{
	this->pivot = new Point(_x, _y);
	this->width = std::abs(_width); // avoid negative width and height;
	this->height = std::abs(_height);
}

/**
Inspiré par SFML Rect<T>::intersects
https://github.com/LaurentGomila/SFML/blob/12d81304e63e333174d943ba3ff572e38abd56e0/include/SFML/Graphics/Rect.inl

Vérifie si deux CollisionBox sont superposés ou partiallement superposé.
@param[in] _otherBox L'autre CollisionBox à vérifier.
@return True si les deux CollisionBox sont superposés, sinon False.
*/
bool CollisionBox::IntersectWith(const CollisionBox& _otherBox, float _deltaX, float _deltaY) const
{

	if (this != &_otherBox)
	{
		if (std::abs(this->getLeft() - _otherBox.getLeft()) < 100 && std::abs(this->getTop() - _otherBox.getTop()) < 100)
		{
			float thisLeft = this->getLeft() + _deltaX;
			float thisRight = this->getRight() + _deltaX;
			float thisTop = this->getTop()+_deltaY;
			float thisBottom = this->getBottom()+_deltaY;

			float otherLeft = _otherBox.getLeft();
			float otherRight = _otherBox.getRight();
			float otherTop = _otherBox.getTop();
			float otherBottom = _otherBox.getBottom();

			//Get the rectangle of the overlapping boxes. I recommand to draw to overlapping boxes to understand this algorithm.
			float possibleIntersectionLeft = std::max(thisLeft, otherLeft);
			float possibleIntersectionRight = std::min(thisRight, otherRight);
			float possibleIntersectionTop = std::max(thisTop, otherTop);
			float possibleIntersectionBottom = std::min(thisBottom, otherBottom);

			if ((possibleIntersectionLeft <= possibleIntersectionRight) && (possibleIntersectionTop <= possibleIntersectionBottom))
			{
				return true;
			}
		}

	}
	return false;
}

CollisionBox::~CollisionBox(void)
{
	delete this->pivot;
}


Point* CollisionBox::ClosestCornerTo(CollisionBox& _otherBox) const
{
	Point* closestCorner = new Point(NULL,NULL);
	if (std::abs(this->getLeft() - _otherBox.getCenterX()) < std::abs(this->getRight() - _otherBox.getCenterX()))
	{
		closestCorner->setX(this->getLeft());
	}
	else
	{
		closestCorner->setX(this->getRight());
	}

	if (std::abs(this->getTop() - _otherBox.getCenterY()) < std::abs(this->getBottom() - _otherBox.getCenterY()))
	{
		closestCorner->setY(this->getTop());
	}
	else
	{
		closestCorner->setY(this->getBottom());
	}
	return closestCorner;
}

/**
Setter de la position en X
@param[in] _x la nouvelle position en X
*/
void CollisionBox::setLeft(float _x)
{
	this->pivot->setX(_x);
}

/**
Setter de la position en Y
@param[in] _y la nouvelle position en Y
*/
void CollisionBox::setTop(float _y)
{
	this->pivot->setY(_y);
}

/**
Getter de la position en X
@return La position en X
*/
float CollisionBox::getLeft(void) const
{
	return this->pivot->getX();
}
/**
Getter de la position en Y
@return La position en Y
*/
float CollisionBox::getTop(void) const
{
	return this->pivot->getY();
}

float CollisionBox::getRight(void) const
{
	return this->getLeft() + this->getWidth();
}

float CollisionBox::getBottom(void) const
{
	return this->getTop() + this->getHeight();
}

void CollisionBox::setHeight(float _height)
{
	this->height = _height;
}

void CollisionBox::setWidth(float _width)
{
	this->width = _width;
}
float CollisionBox::getWidth(void) const
{
	return this->width;
}
float CollisionBox::getHeight(void) const
{
	return this->height;
}

float CollisionBox::getCenterX(void) const
{
	return (this->getLeft() + (this->getWidth()/2.f));
}

float CollisionBox::getCenterY(void) const
{
	return (this->getTop() + (this->getHeight()/2.f));
}

Point* CollisionBox::getPivot(void) const
{
	return this->pivot;
}