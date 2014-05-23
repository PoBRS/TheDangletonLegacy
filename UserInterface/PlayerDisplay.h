#include <SFML/Graphics.hpp>
#include "../SoftwareLogic/Player.h"
#include "WeaponDisplay.h"
class PlayerDisplay : public Observer
{
public:
	PlayerDisplay(void);
	~PlayerDisplay(void);
	sf::Sprite GetSprite(void);
	void Move(void);
	void SetPlayer(Actor* _player);
	sf::FloatRect getBoundingRect(void) const;
	void MoveLeft(void);
	void MoveRight(void);
	void ResetAnimationFrame(int);
	sf::Sprite GetWeapon(void);

private:
	void Notify(void);
	void SetLeftSprite(void);
	void SetRightSprite(void);
	sf::Sprite sprite;
	sf::Texture texture;
	Actor* player;
	sf::Clock clock;
	vector<sf::Sprite*> vectorLeftSprite;
	vector<sf::Sprite*>::iterator itMoveLeft;
	vector<sf::Sprite*>::iterator itMoveRight;
	vector<sf::Sprite*> vectorRightSprite;
	int animationFrame;
	WeaponDisplay* weaponDisplay;



};