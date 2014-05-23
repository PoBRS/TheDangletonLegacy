#include "stdafx.h"
#include "Point.h"

Point::Point(const float _x,const float _y)
{
	this->setX(_x);
	this->setY(_y);
}

float Point::getX(void) const
{
	return this->x;
}

float Point::getY(void) const
{
	return this->y;
}

void Point::setX(const float _x)
{
	this->x = _x;
}

void Point::setY(const float _y)
{
	this->y = _y;
}

bool Point::operator==(const Point& _comparedPoint) const
{
	if (this->getX() == _comparedPoint.getX())
	{
		if (this->getY() == _comparedPoint.getY())
		{
			return true;
		}
	}
	return false;
}