#include "stdafx.h"
#include "Algebra.h"
#include <algorithm>
#include <assert.h>


/**
	Fonction qui indique si deux segments de droite se croisent.
	@param[in] _segment1 Le vertex représentant un premier Segment.
	@param[in] _segment2 Le vertex représentant le deuxième segment.
	@return True si les deux segments se croisent.
	@todo Effectuer les tests sur cette méthode.
	@todo Revoir le code, je n'aime vraiment pas le pointeur de boolean.
*/
bool Algebra::SegmentIntersect(Vertex* _segment1, Vertex* _segment2) const
{

	Point* intersectionPoint = new Point(NULL,NULL);
	bool* retour = NULL;

	/*
	Defines a line equation like so: y = mx+b
	*/


	//Check if a segment is a point
	if (retour == NULL && _segment1->IsPoint())
	{
		retour = new bool(false);
	}
	if (retour == NULL && _segment2->IsPoint())
	{
		retour = new bool(false);
	}

	// -------------- NOW, WE KNOW THEY BOTH ARE LINE --------------------
	//Check if both segments are vertical
	if (retour == NULL && _segment1->IsVertical() && _segment2->IsVertical())
	{
		retour = new bool(false);
	}
	// ---------------- NOW WE KNOW THEY ARE NOT || -----------------

	//Check if both segments are horizontal
	if (retour == NULL && _segment1->IsHorizontal() && _segment2->IsHorizontal())
	{
		retour = new bool(false);
	}
	// --------------- NOW WE KNOW THEY ARE NOT = ---------------------


	if (retour == NULL && _segment1->IsVertical()) //if segment 1 is vertical
	{
		intersectionPoint->setX(_segment1->getStartPoint()->getX());
	}
	else if (retour == NULL && _segment2->IsVertical()) // if segment 2 is vertical
	{
		intersectionPoint->setX(_segment2->getStartPoint()->getX());
	}

	// --------------- NOW WE KNOW WHAT IS THE X INTERSECTION IF ONE OF THEM IS | --------------

	if (retour == NULL && _segment1->IsHorizontal()) //if segment 1 is horizontal
	{
		intersectionPoint->setY(_segment1->getStartPoint()->getY());
	}
	else if (retour == NULL && _segment2->IsHorizontal()) // if segment 2 is horizontal
	{
		intersectionPoint->setY(_segment2->getStartPoint()->getY());
	}

	// --------------- NOW WE KNOW WHAT IS THE Y INTERSECTION IF ONE OF THEM IS __ ----------------


	if (retour == NULL && intersectionPoint->getX() != NULL) // Find the Y intersection
	{

		//Get the yIntersection by finding the other line's equation.
		if (intersectionPoint->getY() == NULL)
		{
			float mLine;
			float bLine;
			//Get the line that is not vertical
			if (!_segment1->IsVertical())
			{
				mLine = this->getSlope(_segment1);
				bLine = this->getOrigin(_segment1->getStartPoint(), mLine);

			}
			else
			{
				mLine = this->getSlope(_segment2);
				bLine = this->getOrigin(_segment2->getStartPoint(), mLine);

			}
			intersectionPoint->setY(mLine * intersectionPoint->getX() + bLine);
		}

		retour = new bool(IsPartOfBothSegment(intersectionPoint, _segment1, _segment2));

	}

	// ----------------- NOW WE KNOW THAT THERE IS NO VERTICAL LINE ----------------------------

	if (retour == NULL && intersectionPoint->getY() != NULL) //Because of the previous block of code, we know that the other line is askew and that we must find xIntersection
	{
		float mLine;
		float bLine;
		//Get the line that is not vertical
		if (!_segment1->IsVertical())
		{
			mLine = this->getSlope(_segment1);
			bLine = this->getOrigin(_segment1->getStartPoint(), mLine);

		}
		else
		{
			mLine = this->getSlope(_segment2);
			bLine = this->getOrigin(_segment2->getStartPoint(), mLine);

		}

		float xIntersection = (intersectionPoint->getY() - bLine)/mLine;
		intersectionPoint->setX(xIntersection);

		retour = new bool(IsPartOfBothSegment(intersectionPoint, _segment1, _segment2));
	}

	//	------------------- NOW, WE KNOW THAT THEY BOTH ARE ASKEW ----------------------
	if (retour == NULL)
	{
		// m = (y2-y1)/(x2-x1)
		float mLine1 = getSlope(_segment1);
		float mLine2 = getSlope(_segment2);

		// b = y-mx
		float bLine1 = this->getOrigin(_segment1->getStartPoint(), mLine1);
		float bLine2 = this->getOrigin(_segment2->getStartPoint(), mLine2);

		//lets find the x of intersection between those two lines.
		//given y1=m1x1+b1 and y2 = m2x2+b2
		// y1 == y2
		// x1 == x2
		//m1x+b1 == m2x+b2
		//m1x-m2x == b2-b1
		//(m1-m2)x == b2-b1
		//x = (b2-b1)/(m1-m2)

		//If they are parallel
		if (mLine1 == mLine2)
		{
			retour = new bool(false);
		}

		// --------------- NOW WE KNOW THAT THEY ARE NOT PARALLEL AND THAT THEREFOR, THERE MUST BE AN INTERSECTION ------------------------

		intersectionPoint->setX((bLine2 - bLine1)/(mLine1-mLine2));

		//We find y by replacing x in one equation;

		intersectionPoint->setY(mLine1* intersectionPoint->getX() + bLine1);

		retour = new bool(IsPartOfBothSegment(intersectionPoint, _segment1, _segment2));
	}
	delete intersectionPoint;
	bool retourTemp = *retour;
	delete retour;
	return retourTemp;
}

/**
	Fonction qui prend vérifie si une valeur est entre deux autres.
	@param[in] _valueToCheck La valeur à vérifier
	@param[in] _value1 La première valeur limite.
	@param[in] _value2 La deuxoème valeur limite.
	@return True s'il est entre les deux, sinon false.
*/
bool Algebra::IsBetween(float _valueToCheck, float _value1, float _value2) const
{
	if (std::min(_value1,_value2) <= _valueToCheck && _valueToCheck <= std::max(_value1, _value2))
	{
		return true;
	}
	return false;
}

/**
	Fonction qui vérifie si un point appartiennent à deux segments.
	@param[in] _pointToCheck Le point a vérifier s'il appartient aux deux segments.
	@param[in] _segment1 Le premier Segment.
	@param[in] _segment2 Le deuxième Segment.
	@return true si le point appartient au deux segment, sinon, false.
	@see IsPartOf
*/

bool Algebra::IsPartOfBothSegment(const Point* _pointToCheck, const Vertex* _segment1, const Vertex* _segment2) const
{
	if (IsPartOf(_pointToCheck, _segment1))
	{
		if (IsPartOf(_pointToCheck, _segment2))
		{
			return true;
		}
	}
	return false;
}

/**
	Fonction qui vérifie si les coordonnées d'un point appartiennent à un segment.
	@param[in] _pointToCheck Le point a vérifier s'il appartient à un segment de droite.
	@param[in] _segment Le segment de droite.
	@return true si le point appartient au segment, sinon false.
	@see IsBetween
*/
bool Algebra::IsPartOf(const Point* _pointToCheck, const Vertex* _segment) const
{
	if (IsBetween(_pointToCheck->getX(), _segment->getStartPoint()->getX(), _segment->getEndPoint()->getX()))
	{
		if (IsBetween(_pointToCheck->getY(), _segment->getStartPoint()->getY(), _segment->getEndPoint()->getY()))
		{
			return true;
		}
	}
	return false;
}


/**
	Fonction qui calcule la pente d'une segment.
	Elle va utiliser les coordonnes de deux points du segment.
	@param[in] _segment Le segment à trouver la pente
	@exception Ne peux pas trouver la pente d'un segment vertical.
*/
float Algebra::getSlope(Vertex* _segment) const
{
	// m = y2-y1/x2-x1
	assert(_segment != NULL);
	assert(_segment->IsVertical());
	return (_segment->getEndPoint()->getY() - _segment->getStartPoint()->getY()) /( _segment->getEndPoint()->getX() - _segment->getStartPoint()->getX());
}

/**
	Fonction qui trouve le point d'origine d'une droite à l'aide d'un point et de sa pente.
	@param[in] _point Un point appartenant à une droite.
	@param[in] _slope La pente de la droite.
*/
float Algebra::getOrigin(Point* _point, float _slope) const
{
	// b = y-mx
	assert(_point != NULL);
	return _point->getY() - (_slope * _point->getX());
}