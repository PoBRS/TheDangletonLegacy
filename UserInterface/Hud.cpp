#include "Hud.h"
#include "../DataDeposit/ScoreReader.h"

Hud::Hud(Player* _player)
{

	this->player = _player;
	this->SetFrameHeart();
	this->SetLife();
	this->SetPoints();
	this->points = 0;
	sf::Text textPoints;



	
	if(!this->font.loadFromFile("Ressources/emulogic.ttf"))
	{

	}
	else
	{
			textPoints.setPosition(425.f, 5.f);
			textPoints.setFont(font);
			textPoints.setString("Points:");
			textPoints.setScale(0.6f,0.6f);
			this->highScoreText.setPosition(425.f,30.f);
			this->highScoreText.setFont(font);
			this->highScoreText.setScale(0.5f, 0.5f);
	}
	
	text = textPoints;
}

Hud::~Hud(void)
{
	
	for(unsigned int i = 0 ; i < vectorFrameHeart.size(); i ++)
	{
		delete vectorFrameHeart[i];
	}
	
}

void Hud::SetPoints(void)

{
		this->points = this->player->GetPoints();
		text.setString("Points:" + to_string(this->points));
}

void Hud::setHighScore(void)
{
		ScoreReader reader("../DataDeposit/Ressources/Scores.txt");
		this->highScore = reader.getScoreVector()->begin()->first;
		this->highScoreText.setString("Meilleur:" + to_string(this->highScore));
}

vector<sf::Sprite> Hud::GetLife(void)
{
	this->SetLife();
	return vectorSpriteHealth;
}
sf::Text Hud::GetPoints(void)
{
	this->SetPoints();
	return text;
}

sf::Text Hud::GetHighScore(void)
{
	this->setHighScore();
	return this->highScoreText;
}
void Hud::SetLife(void)
{
	vectorSpriteHealth.erase(vectorSpriteHealth.begin(), vectorSpriteHealth.end());
	vectorSpriteHealth.clear();

	this->nbLife = player->GetNbLife();
	
	float positionY = 10.f;
	float positionX = 10.f;
	for(int i = 0; i < this->nbLife; i++)
	{
		vectorSpriteHealth.push_back(*vectorFrameHeart[0]);
		vectorSpriteHealth[i].setPosition(positionX, positionY);
		positionX += 30.f;
		
	}

	

}
void Hud::SetFrameHeart(void)
{
	sf::Sprite heartSprite;
	if (!this->texture.loadFromFile("Ressources/heartSprite.png"))
	{

	}
	else
	{
		sf::Sprite* sprite = new sf::Sprite();
		heartSprite.setTexture(texture);
		heartSprite.setPosition(10.f, 10.f);

		heartSprite.setTextureRect(sf::IntRect(5, 5, 26, 26));
		*sprite = heartSprite;
		vectorFrameHeart.push_back(sprite);
		heartSprite.setTextureRect(sf::IntRect(35, 5, 26, 26));
		sprite = new sf::Sprite();
		*sprite = heartSprite;
		vectorFrameHeart.push_back(sprite);
		heartSprite.setTextureRect(sf::IntRect(65, 5, 26, 26));
		sprite = new sf::Sprite();
		*sprite = heartSprite;
		vectorFrameHeart.push_back(sprite);
		heartSprite.setTextureRect(sf::IntRect(95, 5, 26, 26));
		sprite = new sf::Sprite();
		*sprite = heartSprite;
		vectorFrameHeart.push_back(sprite);
	
		
	}
}