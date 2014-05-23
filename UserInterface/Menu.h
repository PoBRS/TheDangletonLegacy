#include <SFML/Graphics.hpp>
#include "Game.h"
class Menu
{
public:
	Menu(void);
	~Menu(void);
	void SetupMenu(void);
	void ProcessEvents(void);
	void Run(void);
	void RenderInWindow(void);
	void HandleKeyInput(sf::Keyboard::Key _key, bool _isPressed);
	void UpdateMenu(void);
private:
	sf::RenderWindow mWindow;
	sf::Text  titlePart1;
	
	sf::Text  titlePart2;
	sf::Text  textDeveloppers;
	sf::Text  textBegin;
	sf::Font font;
	Game* game;
};

