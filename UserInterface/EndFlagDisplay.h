#include <SFML/Graphics.hpp>
#include "../SoftwareLogic/Actor.h"


class EndFlagDisplay: public Observer
{
public:
	EndFlagDisplay(void);
	~EndFlagDisplay(void);
	void SetEndFlag(Actor* _endFlag);
	Actor* GetEndFlag(void);
	void SetSpritePosition(void);
	sf::Sprite GetSprite(void);
	void Notify(void);

private:
	Actor* EndFlag;
	sf::Texture texture;
	sf::Sprite sprite;

	
};

