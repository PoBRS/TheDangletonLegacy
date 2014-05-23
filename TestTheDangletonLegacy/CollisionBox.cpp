#include "stdafx.h"
#include "CppUnitTest.h"
#include <cassert>
#include "../SoftwareLogic/CollisionBox.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestCollision
{		
	TEST_CLASS(Collision)
	{
	public:
		/*************************************************************************\
		***		***		***								***		***		***		***
		***		***		***			ClosestCornerTo		***		***		***		***
		***		***		***								***		***		***		***
		\**************************************************************************/
		
		TEST_METHOD(A_GivenClosestCornerTo_WhenAisPerfectlyAboveBWithoutTouching_Then_ReturnEitherBottomLeftOrBottomRight)
		{
			CollisionBox foo(10,10,10,10);
			CollisionBox bar(10,30,10,10);
			Assert::IsTrue((foo.getLeft() == foo.ClosestCornerTo(bar)->getX() || foo.getRight() == foo.ClosestCornerTo(bar)->getX()),L"[X] Taille: identique. Position: Au-dessus, Parfaitement centrés",LINE_INFO());
			Assert::AreEqual(foo.getBottom(), foo.ClosestCornerTo(bar)->getY(),L"[Y] Taille: identique. Position: Au-dessus, Parfaitement centrés",LINE_INFO());
		}

		TEST_METHOD(B_GivenClosestCornerTo_WhenAisPerfectlyLeftToBWithoutTouching_Then_ReturnEitherTopRightOrBottomRight)
		{
			CollisionBox foo(10,10,10,10);
			CollisionBox bar(30,10,10,10);
			Assert::AreEqual(foo.getRight(), foo.ClosestCornerTo(bar)->getX(),L"[X] Taille: identique. Position: Gauche, Parfaitement centrés",LINE_INFO());
			Assert::IsTrue((foo.getTop() == foo.ClosestCornerTo(bar)->getY() || foo.getBottom() == foo.ClosestCornerTo(bar)->getY()),L"[Y] Taille: identique. Position: Gauche, Parfaitement centrés",LINE_INFO());
		}

		TEST_METHOD(C_GivenClosestCornerTo_WhenAisPerfectlyUnderBWithoutTouching_Then_ReturnEitherTopLeftOrTopRight)
		{
			CollisionBox foo(10,30,10,10);
			CollisionBox bar(10,10,10,10);
			Assert::IsTrue((foo.getLeft() == foo.ClosestCornerTo(bar)->getX() || foo.getRight() == foo.ClosestCornerTo(bar)->getX()),L"[X] Taille: identique. Position: Dessous, Parfaitement centrés",LINE_INFO());
			Assert::AreEqual(foo.getTop(), foo.ClosestCornerTo(bar)->getY(),L"[Y] Taille: identique. Position: Dessous, Parfaitement centrés",LINE_INFO());
		}
		TEST_METHOD(D_GivenClosestCornerTo_WhenAisPerfectlyRightToBWithoutTouching_Then_ReturnEitherTopLeftOrBottomLeft)
		{
			CollisionBox foo(30,10,10,10);
			CollisionBox bar(10,10,10,10);
			Assert::AreEqual(foo.getLeft(), foo.ClosestCornerTo(bar)->getX(),L"[X] Taille: identique. Position: Gauche, Parfaitement centrés",LINE_INFO());
			Assert::IsTrue((foo.getTop() == foo.ClosestCornerTo(bar)->getY() || foo.getBottom() == foo.ClosestCornerTo(bar)->getY()),L"[Y] Taille: identique. Position: Gauche, Parfaitement centrés",LINE_INFO());
		}
		TEST_METHOD(E_GivenClosestCornerTo_WhenAisPerfectlyCentredToB_ThenReturnSomething)
		{
			CollisionBox foo(10,10,10,10);
			CollisionBox barBigger(0,0,30,30);
			CollisionBox barSame(10,10,10,10);
			CollisionBox barSmaller(12,12,6,6);

			Assert::IsNotNull(foo.ClosestCornerTo(barBigger),L"Taille: A plus petit que B. Position: Centré",LINE_INFO());
			Assert::IsNotNull(foo.ClosestCornerTo(barSame),L"Taille: A même taille que B. Position: Centré",LINE_INFO());
			Assert::IsNotNull(foo.ClosestCornerTo(barSmaller),L"Taille: A plus grand que B. Position: Centré",LINE_INFO());
		}

		TEST_METHOD(F_GivenClosestCornerTo_WhenCornerAisTouchingCenterB_ThenReturnCornerA)
		{
			CollisionBox fooBigger(10,10,100,100);
			CollisionBox fooSame(10,10,20,20);
			CollisionBox fooSmaller(10,10,10,10);

			CollisionBox bar(0,0,20,20);

			Point centredPoint(10,10);
			Assert::AreEqual(centredPoint.getX(), fooBigger.ClosestCornerTo(bar)->getX(),L"[X]Foo est plus gros et son coin touche le centre de Bar",LINE_INFO());
			Assert::AreEqual(centredPoint.getX(), fooSame.ClosestCornerTo(bar)->getX(),L"[X]Foo est de même taille et son coin touche le centre de Bar",LINE_INFO());
			Assert::AreEqual(centredPoint.getX(), fooSmaller.ClosestCornerTo(bar)->getX(),L"[X]Foo est plus petit et son coin touche le centre de Bar",LINE_INFO());
			Assert::AreEqual(centredPoint.getY(), fooBigger.ClosestCornerTo(bar)->getY(),L"[Y]Foo est plus gros et son coin touche le centre de Bar",LINE_INFO());
			Assert::AreEqual(centredPoint.getY(), fooSame.ClosestCornerTo(bar)->getY(),L"[Y]Foo est de même taille et son coin touche le centre de Bar",LINE_INFO());
			Assert::AreEqual(centredPoint.getY(), fooSmaller.ClosestCornerTo(bar)->getY(),L"[Y]Foo est plus petit et son coin touche le centre de Bar",LINE_INFO());
		}


		/*************************************************************************\
		***		***		***								***		***		***		***
		***		***		***			IntersectWith		***		***		***		***
		***		***		***								***		***		***		***
		\**************************************************************************/
		
		TEST_METHOD(G_GivenIntersectWith_WhenCollisionBoxesArentTouching_ThenReturnFalse)
		{
			CollisionBox foo(100,100,10,10);
			CollisionBox barToTheLeft(0,100,10,10);
			CollisionBox barToTheRight(200,100,10,10);
			CollisionBox barToTheTop(100,0,10,10);
			CollisionBox barToTheBottom(100,200,10,10);
			CollisionBox barToTheTopLeft(0,0,10,10);
			CollisionBox barToTheTopRight(200,0,10,10);
			CollisionBox barToTheBottomLeft(0,200,10,10);
			CollisionBox barToTheBottomRight(200,200,10,10);

			Assert::IsFalse(foo.IntersectWith(barToTheBottom),L"Bar est en bas de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheBottomLeft),L"Bar est en bas à gauche de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheBottomRight),L"Bar est en bas à droite de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheTop),L"Bar est en haut de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheTopLeft),L"Bar est en haut à gauchede foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheTopRight),L"Bar est en haut à droite de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheLeft),L"Bar est à gauche de foo",LINE_INFO());
			Assert::IsFalse(foo.IntersectWith(barToTheRight),L"Bar est à droite de foo",LINE_INFO());

		}

		TEST_METHOD(H_GivenInterSectWith_WhenCollisionBoxesAreTouching_ThenReturnTrue)
		{
			CollisionBox foo(50,50,100,100);
			CollisionBox barExclusivelyLeft(100,100,300,20);
			CollisionBox barExclusivelyBottom(100,100,20,300);
			CollisionBox barExclusivelyTop(100,25,10,50);
			CollisionBox barExclusivelyRight(25,100,50,10);
			CollisionBox barTopLeft(0,0,100,100);
			CollisionBox barTopRight(75,25,100,100);
			CollisionBox barBottomLeft(0,75,100,100);
			CollisionBox barBottomRight(75,75,100,100);
			CollisionBox barTopBottom(75,0,10,300);
			CollisionBox barLeftRight(0,75,300,10);
			CollisionBox barAround(0,0,600,600);
			CollisionBox barInside (75,75,10,10);

			Assert::IsTrue(foo.IntersectWith(barAround),L"Foo tient en entier à l'interieur de Bar",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barInside),L"Foo contient bar en entier", LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barExclusivelyBottom),L"Bar touche au dessous de foo",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barExclusivelyTop),L"Bar touche au dessus de foo",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barExclusivelyLeft),L"Bar touche à gauche de foo",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barExclusivelyRight),L"Bar touche à droite de foo",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barTopBottom),L"Bar traverse foo de bas en haut",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barLeftRight),L"Bar traverse foo de gauche à droite",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barTopLeft),L"Bar traverse foo en haut et à gauche",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barTopRight),L"Bar traverse foo en haut et à droite",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barBottomLeft),L"Bar traverse foo en bas et à gauche",LINE_INFO());
			Assert::IsTrue(foo.IntersectWith(barBottomRight),L"Bar traverse foo en haut et à gauche",LINE_INFO());


		}

	};
}