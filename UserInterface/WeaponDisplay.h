
#include <SFML/Graphics.hpp>

class WeaponDisplay
{
public:
	WeaponDisplay(void);
	~WeaponDisplay(void);
	void AttackLeft(void);
	void AttackRight(void);
	sf::Sprite GetSprite(void);
	void SetPosition(float _x, float _y);
	void Notify(void);
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

