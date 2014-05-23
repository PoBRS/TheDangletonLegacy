#ifndef _DEBUG
#define NDEBUG
#endif
#include <cassert>
#include "Game.h"
#include <string>
#include "../DataDeposit/ScoreReader.h"
#include "../SoftwareLogic/SceneEntities.h"
sf::Event event;

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const float PLAYER_SPEED = 175.f;

const std::string WINDOW_TITLE = "The Dangleton Legacy";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 50.f);
const std::string LEVEL_PATH = "../DataDeposit/Ressources/Level1.txt";

Game::Game(void): mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
	SceneEntities::getInstance().CleanMap();
	this->currentMap = new Map(LEVEL_PATH);
	this->view.reset(sf::FloatRect(0, 0, 640, 430));
	this->view.setViewport(sf::FloatRect(0,0.10, 1, 1));
	HUD_view.reset(sf::FloatRect(0, 0, 640,50));
	HUD_view.setViewport(sf::FloatRect(0,0, 1, 0.10f));

	this->background = new Background("Ressources/Background.png");
	this->mWindow.setView(this->HUD_view);
	this->mWindow.setView(this->view);
	this->SetEndFlag();
	this->mIsMovingUp = false;
	this->mIsMovingDown = false;
	this->mIsMovingLeft = false;
	this->mIsMovingRight = false;
	this->mIsJumping = false;
	this->music.BackGroundMusic();
	this->SetPlayer();
	this->SetVectorEnemy();
	this->SetCollectible();
}

void Game::SetPlayer(void)
{
	this->player = (Actor*)SceneEntities::getInstance().CreateEntity(EnumEntities::PLAYER);
	this->hud = new Hud((Player*)player);
	this->player->setWidth(32);
	this->player->setHeight(32);
	this->player->SetSpeed(10);
	this->playerDisplay = new PlayerDisplay();
	this->player->AddObserver(*playerDisplay);
	this->playerDisplay->SetPlayer((Player*)player);
	this->player->SetPosition(200,200); 
}

void Game::SetCollectible(void)
{

	vector<int> x= this->currentMap->GetpositionXCollectible();
	vector<int> y = this->currentMap->GetpositionYCollectible();
	for(int i =  0; i < x.size(); i++)
	{
		Actor *collectible = (Actor*)SceneEntities::getInstance().CreateEntity(EnumEntities::COLLECTIBLE);


		CollectibleDisplay* collectibleDisplay = new CollectibleDisplay();
		collectible->AddObserver(*collectibleDisplay);
		collectibleDisplay->SetCollectible((Actor*)collectible);

		collectible->SetPosition(y[i] * 50, x[i] * 50); 

		collectible->setWidth(26);
		collectible->setHeight(19);
		collectible->SetNbLife(1);

		vectorCollectible.push_back(collectible);
		vectorCollectibleDisplay.push_back(collectibleDisplay);

	}
}

void Game::SetVectorEnemy(void)
{

	vector<int> x = this->currentMap->GetpositionXEnemy();
	vector<int> y = this->currentMap->GetpositionYEnemy();
	for(int i =  0; i < x.size(); i++)
	{
		Actor *enemy = (Actor*)SceneEntities::getInstance().CreateEntity(EnumEntities::ENEMY);
		enemy->SetSpeed(-1);
		EnemyDisplay* enemyDisplay = new EnemyDisplay();
		enemy->AddObserver(*enemyDisplay);
		enemyDisplay->SetEnemy((Enemy*)enemy);
		enemy->SetPosition(y[i] * 50, x[i] * 50); 
		enemy->setWidth(20);
		enemy->setHeight(20);
		enemy->SetNbLife(1);

		vectorEnemy.push_back(enemy);
		vectorEnemyDisplay.push_back(enemyDisplay);

	}

}

/** 
Destructeur de Game. Ajoute le score du joueur.
*/
Game::~Game(void)
{

	delete player;
	delete hud;
	delete playerDisplay;
	for(unsigned int i = 0; i < vectorEnemy.size(); i++)
	{
		delete vectorEnemy[i];
	}
	for(unsigned int i = 0; i < vectorEnemyDisplay.size(); i++)
	{
		delete vectorEnemyDisplay[i];
	}
	for(unsigned int i = 0; i < vectorCollectible.size(); i++)
	{
		delete vectorCollectible[i];
	}
	for(unsigned int i = 0; i < vectorCollectibleDisplay.size(); i++)
	{
		delete vectorCollectibleDisplay[i];
	}
	delete this->currentMap;
	delete this->endFlag;
	delete this->endFlagDisplay;
	delete this->background;
}
void Game::EndGame(void)
{
	ScoreReader reader("../DataDeposit/Ressources/Scores.txt");
	reader.AddNewScore(((Player*)this->player)->GetPoints(),"N/A");

	mWindow.close();
}

bool Game::IsEndGame(void)
{
	if(player->GetNbLife() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Game::run(void)
{
	GameSetup();
}
/**
	Servira à assurer un framerate constant et empêcher des problèmes de collisions avec le lag.
	Assure que les mêmes valeurs seront entrées dans l'update de Move(), peu importe la machine.
	@bug : Si jamais la boucle de temps est trop lente et que ça prend plus de temps faire l'update
			de game que ce qui le maximum de temps, ceci empêche le rafraichissement de l'image entraintant des framerates sous 1fps.
*/
void Game::GameSetup(void)
{
	sf::Clock clock;

	
	sf::Time timeSinceLastUpdate = sf::Time::Zero; 

	while (mWindow.isOpen())
	{
		ProcessEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			ProcessEvents();
			UpdateGame();
		}
		RenderInWindow();
	}
	ProcessEvents();
	UpdateGame();
	RenderInWindow();

}

void Game::ProcessEvents(void)
{
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				HandleKeyInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				HandleKeyInput(event.key.code, false);
				ResetAnimation();
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}
	}
}


void Game::HandleKeyInput(sf::Keyboard::Key _key, bool _isPressed)
{
	if (_key == sf::Keyboard::W)
		mIsMovingUp = _isPressed;
	if (_key == sf::Keyboard::S)
		mIsMovingDown = _isPressed;
	if (_key == sf::Keyboard::A)
		mIsMovingLeft = _isPressed;
	if (_key == sf::Keyboard::D)
		mIsMovingRight = _isPressed;
	if (_key == sf::Keyboard::Space)
	{
		this->mIsJumping = _isPressed;
		this->music.JumpSound();
	}

}

void Game::UpdateGame(void)
{
	if(this->IsEndGame())
	{
		this->EndGame();
	}

	if (mIsMovingLeft && !mIsMovingRight)
	{
		player->MoveLeft();
		playerDisplay->MoveLeft();

	}
	if (mIsMovingRight && !mIsMovingLeft)
	{
		player->MoveRight();
		playerDisplay->MoveRight();

	}

	if (this->mIsJumping)
	{
		player->Jump();
	}


	this->player->UpdatePosition();

	this->view.setCenter(player->getCenterX(), player->getCenterY());


	this->CheckEnemyDeath();
	for (int unsigned i = 0; i < vectorEnemyDisplay.size(); i ++)
	{
		if(vectorEnemy[i]->IsFacingLeft())
		{
			vectorEnemyDisplay[i]->SetMoveLeft(true);
		}
		else
		{
			vectorEnemyDisplay[i]->SetMoveLeft(false);
		}


		if(vectorEnemyDisplay[i]->GetMoveLeft())
		{
			vectorEnemy[i]->MoveLeft();
			vectorEnemyDisplay[i]->MoveLeft();
		}
		else
		{
			vectorEnemy[i]->MoveRight();
			vectorEnemyDisplay[i]->MoveRight();
		}
		vectorEnemy[i]->UpdatePosition();

	}
}


void Game::RenderInWindow(void)
{
	mWindow.clear();
	this->mWindow.setView(this->background_view);
	this->mWindow.draw(this->background->getSprite());
	this->mWindow.setView(this->HUD_view);
	this->SeeHud();
	this->mWindow.setView(this->view);
	this->DisplayEnemy();
	this->currentMap->displayMap(mWindow);
	this->DisplayCollectible();
	this->DisplayEndFlag();
	mWindow.draw(playerDisplay->GetSprite());
	mWindow.display();
}
void Game::ResetAnimation(void)
{
	playerDisplay->ResetAnimationFrame(0);
}
void Game::SeeHud(void)
{


	vector<sf::Sprite> vectorHealth = hud->GetLife();

	for(unsigned int i = 0; i < vectorHealth.size(); i++)
	{
		mWindow.draw(vectorHealth[i]);
	}

	mWindow.draw(hud->GetPoints());
	mWindow.draw(hud->GetHighScore());
}
void Game::DisplayEnemy(void)
{

	this->CheckEnemyDeath();

	for (unsigned int i = 0; i < vectorEnemy.size(); i ++)
	{
		mWindow.draw(vectorEnemyDisplay[i]->GetSprite());
	}

}

void Game::DisplayCollectible(void)
{

	this->CheckCollectedCollectible();
	for (unsigned int i = 0; i < vectorCollectible.size(); i ++)
	{

		mWindow.draw(vectorCollectibleDisplay[i]->GetSprite());

	}
}

void Game::CheckCollectedCollectible(void)
{
	bool damage = false;

	int j = 0;
	for (unsigned int i = 0; i < vectorCollectible.size(); i ++)
	{
		vectorCollectible[i]->CheckCollision();
		if(vectorCollectible[i]->GetNbLife() == 0)
		{
			j = i;
			damage = true;
		}


	}
	if(vectorCollectible.size() != 0 && damage)
	{

		((Player*)this->player)->SetPoints(((Player*)this->player)->GetPoints() + 10);

		delete vectorCollectibleDisplay[j];
		delete vectorCollectible[j];
		vectorCollectibleDisplay.erase(vectorCollectibleDisplay.begin()+j);
		vectorCollectible.erase(vectorCollectible.begin()+j);
		damage = false;
	}
}

void Game::CheckEnemyDeath(void)
{
	float X;
	float Y;
	bool damage = false;

	if(vectorEnemy.size() != 0)
	{
		vector <EnemyDisplay*>::iterator deleteIteratorEnemyDisplay = vectorEnemyDisplay.begin();
		while (deleteIteratorEnemyDisplay != vectorEnemyDisplay.end()) {
			if((*deleteIteratorEnemyDisplay)->GetEnemy()->GetNbLife() == 0)
			{
				delete (*deleteIteratorEnemyDisplay);
				deleteIteratorEnemyDisplay = vectorEnemyDisplay.erase(deleteIteratorEnemyDisplay);
			}
			else
			{
				deleteIteratorEnemyDisplay++;
			}
		}
		vector <Actor*>::iterator deleteIteratorEnemy = vectorEnemy.begin();
		while (deleteIteratorEnemy != vectorEnemy.end()) {
			if((*deleteIteratorEnemy)->GetNbLife() == 0)
			{
				delete *deleteIteratorEnemy;
				deleteIteratorEnemy = vectorEnemy.erase(deleteIteratorEnemy);
			}
			else
			{
				deleteIteratorEnemy++;
			}
		}
		

	}
}

void Game::DisplayEndFlag(void)
{
	this->CheckEndFlagCollision();
	mWindow.draw(this->endFlagDisplay->GetSprite());
}
void Game::CheckEndFlagCollision(void)
{
	this->endFlag->CheckCollision();
	if(endFlag->GetNbLife() == 0)
	{
		this->EndGame();
	}
}
void Game::SetEndFlag(void)


{
	this->endFlag = (Actor*)SceneEntities::getInstance().CreateEntity(EnumEntities::ENDFLAG);

	this->endFlagDisplay = new EndFlagDisplay();
	endFlag->AddObserver(*endFlagDisplay);
	endFlagDisplay->SetEndFlag((Actor*)endFlag);

	endFlag->SetPosition(4500, 400); 
	endFlag->setWidth(38);
	endFlag->setHeight(38);
	endFlag->SetSpeed(0);
	endFlag->SetNbLife(1);

	this->endFlag = endFlag;
	this->endFlagDisplay = endFlagDisplay;

}