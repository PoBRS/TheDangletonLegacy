#include "Menu.h"

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const float PLAYER_SPEED = 175.f;

const std::string WINDOW_TITLE = "The Dangleton Legacy";
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);


Menu::Menu(void)  : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
{
	this->game = NULL;
	UpdateMenu();
}

Menu::~Menu(void)
{
	delete game;
}
void Menu::SetupMenu(void)
{
	// Servira à assurer un framerate constant et empêcher des problèmes de collisions avec le lag.
	// Assure que les mêmes valeurs seront entrées dans l'update de Move(), peu importe la machine.
	sf::Time timeSinceLastUpdate = sf::Time::Zero; 

	while (mWindow.isOpen())
	{
		ProcessEvents();


		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			ProcessEvents();

		}
		RenderInWindow();
	}
	ProcessEvents();

	RenderInWindow();

}
void Menu::Run(void)
{
	SetupMenu();
}

void Menu::ProcessEvents(void)
{
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:
				HandleKeyInput(event.key.code, true);
				break;
			}
		}
	}
}


void Menu::HandleKeyInput(sf::Keyboard::Key _key, bool _isPressed)
{
	if (_key == sf::Keyboard::Space)
	{
		mWindow.setVisible(false);

		if (this->game == NULL)
		{
			game = new Game();
		}
		game->run();
		delete this->game;
		this->game = NULL;
		mWindow.setVisible(true);

	}

}
void Menu::UpdateMenu(void)
{



	// Affiche le nombre de points en haut à droite


	if(!this->font.loadFromFile("Ressources/emulogic.ttf"))
	{

	}
	else
	{
		std::string points  = "0";

		textBegin.setPosition(170.f, 200.f);
		textBegin.setFont(font);
		textBegin.setString("Press Space");

		titlePart1.setPosition(130.f, 50.f);
		titlePart1.setFont(font);
		titlePart1.setString("The Dangleton");
		titlePart1.setColor(sf::Color::Yellow);

		titlePart2.setPosition(240.f, 70.f);
		titlePart2.setFont(font);
		titlePart2.setCharacterSize(48);
		titlePart2.setString("Legacy");
		titlePart2.setColor(sf::Color::Red);


		textDeveloppers.setPosition(25.f, 400.f);
		textDeveloppers.setFont(font);
		textDeveloppers.setCharacterSize(9);
		textDeveloppers.setString("© - TP3 - Pierre-Olivier Boulet - Raphaël Sylvain - Laurie Lavoie");




	}


}


void Menu::RenderInWindow(void)
{
	mWindow.clear();
	mWindow.draw(textDeveloppers);
	mWindow.draw(titlePart1);
	mWindow.draw(titlePart2);
	mWindow.draw(textBegin);
	mWindow.display();
}