#include <SFML/Graphics.hpp>
#include "../SoftwareLogic/Actor.h"

class CollectibleDisplay: public Observer
{
public:
	CollectibleDisplay(void);
	~CollectibleDisplay(void);
	void SetCollectible(Actor* _collectible);
	Actor* GetCollectible(void);
	void SetSpritePosition(void);
	sf::Sprite GetSprite(void);
	void Notify(void);

private:
	Actor* collectible;
	sf::Texture texture;
	sf::Sprite sprite;

	
};

