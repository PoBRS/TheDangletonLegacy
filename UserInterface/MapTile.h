//#include "../SoftwareLogic/CollisionBox.h"
#include "../SoftwareLogic/SceneEntities.h"
class MapTile : public CollisionBox
{
	public:
		MapTile(void);
		~MapTile(void);
		void DisplayTile(void);
		void AssignValue(int _valueX, int _valueY);
		void AssignPosition(int _valueX, int _valueY);

		int getTileValueX(void);
		int getTileValueY(void);
		int getPositionX(void);
		int getPositionY(void);
	private:
		int tileValueX;
		int tileValueY;
		int positionX;
		int positionY;
};