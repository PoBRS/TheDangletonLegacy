#include <SFML/Graphics.hpp>
#include "../SoftwareLogic/Enemy.h"
class EnemyDisplay : public Observer
{
public:
	EnemyDisplay(void);
	~EnemyDisplay(void);
	sf::Sprite GetSprite(void);
	void Move(void);
	void SetEnemy(Enemy* _enemy);
	sf::FloatRect getBoundingRect(void) const;
	void MoveLeft(void);
	void MoveRight(void);
	void ResetAnimationFrame(int);
	bool GetMoveLeft(void);
	void SetMoveLeft(bool _moveLeft);
	Actor* GetEnemy(void);
private:
	void Notify(void);
	void SetLeftSprite(void);
	void SetRightSprite(void);
	sf::Sprite sprite;
	sf::Texture texture;
	Actor* enemy;
	vector<sf::Sprite*> vectorLeftSprite;
	vector<sf::Sprite*>::iterator itMoveLeft;
	vector<sf::Sprite*>::iterator itMoveRight;
	vector<sf::Sprite*> vectorRightSprite;
	int animationFrame;
	bool moveLeft;
};