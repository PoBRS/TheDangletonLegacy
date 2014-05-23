#ifndef _POINT_H
#define _POINT_H
class Point
{
public:
	Point(const float _x, const float _y);
	bool operator==(const Point& _comparedPoint) const;
	float getX(void) const;
	float getY(void) const;
	void setX(const float _x);
	void setY(const float _y);
private: 
	float x;
	float y;
};

#endif