#include <SFML/Graphics.hpp>

#include "../SoftwareLogic/Player.h"
#include  "../SoftwareLogic/Enemy.h"
#include "../SoftwareLogic/SceneEntities.h"
#include "../SoftwareLogic/SceneEntities.h"

#include "Music.h"
#include "Background.h"
#include "CollectibleDisplay.h"
#include "EndFlagDisplay.h"
#include "Map.h"
#include "EnemyDisplay.h"
#include "Hud.h"
#include "PlayerDisplay.h"

class Game
{

public:
	Game(void);
	~Game(void);
	void run(void);

private:
	void HandleKeyInput(sf::Keyboard::Key _key, bool _isPressed);

	void ResetAnimation(void);
	void SetPlayer(void);
	void GameSetup(void);
	void UpdateGame(void);
	void RenderInWindow(void);
	void ProcessEvents(void);
	void GameShutdown(void);
	void SeeHud(void);
	void DisplayEnemy(void);
	void SetVectorEnemy(void);
	void EndGame(void);
	void DisplayCollectible(void);
	bool IsEndGame(void);
	void CheckEnemyDeath(void);
	void CheckCollectedCollectible(void);
	void CheckEndFlagCollision(void);
	void DisplayEndFlag(void);
	void SetEndFlag(void);
	void SetCollectible(void);
	void SetViews(void);
	Music music;
	Hud* hud;
	vector<EnemyDisplay*> vectorEnemyDisplay;
	Actor* player;
	PlayerDisplay* playerDisplay;
	vector<Actor*> vectorEnemy;
	Map* currentMap;
	Background* background;

	vector<CollectibleDisplay*> vectorCollectibleDisplay;
	vector<Actor*> vectorCollectible;
	EndFlagDisplay* endFlagDisplay;
	Actor* endFlag;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	bool mIsJumping;

	sf::RenderWindow mWindow;
	sf::View view;
	sf::View HUD_view;
	sf::View background_view;
	sf::Clock clock;
};
