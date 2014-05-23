#include <vector>
#include <SFML/Graphics.hpp>
#include "../SoftwareLogic/Player.h"
class Hud
{
	public:
		Hud(Player* _player);
		~Hud(void);
		vector<sf::Sprite> GetLife(void);
		sf::Text GetPoints(void);
		sf::Text GetHighScore(void);

		
	private:
	
		int nbLife;
		int points;
		int highScore;
		void SetLife(void);
		void SetPoints(void);
		void setHighScore(void);
		Player* player;
		vector<sf::Sprite*> vectorFrameHeart;
		vector<sf::Sprite> vectorSpriteHealth;
		void SetFrameHeart(void);
		sf::Texture texture;
		sf::Text text;
		sf::Text highScoreText;
		sf::Font font;
};

