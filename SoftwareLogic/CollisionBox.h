#ifndef _COLLISION_BOX_H
#define _COLLISION_BOX_H

#include "Point.h"

class CollisionBox
{
public:
	bool IntersectWith(const CollisionBox& _otherBox, float _deltaX=0.f, float _deltaY=0.f) const;
	//void ClosestCornerTo(float& _cornerPositionX, float& _cornerPositionY, CollisionBox& _otherBox);
	Point* ClosestCornerTo(CollisionBox& _otherBox) const;
	void setWidth(float _width);
	void setHeight(float _height);
	float getWidth(void) const;
	float getHeight(void) const;
	float getLeft(void) const;
	float getRight(void) const;
	float getBottom(void) const;
	float getTop(void) const;
	float getCenterX(void) const;
	float getCenterY(void) const;
	CollisionBox(float _x=0, float _y=0, float _width=0, float _height=0);
	~CollisionBox(void);
	Point* getPivot(void) const;
protected:

	void setLeft(float _x);
	void setTop(float _y);
private:
	Point* pivot;
	float width;
	float height;
	CollisionBox(const CollisionBox& _toCopy);
	
};


#endif