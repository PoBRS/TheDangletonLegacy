
#include "Music.h"
#include <iostream>
Music::Music(void)
{
	this->musicBack = new sf::Music();
	this->jumpSound = new sf::Sound();
	this->attackSound = new sf::Sound();
	this->buffer = new sf::SoundBuffer();
      
    if (this->buffer->loadFromFile("Ressources/mb_jump.wav"))
	{
		this->jumpSound->setBuffer(*buffer);
	}

	
}

Music::~Music(void)
{
	delete musicBack;
	delete jumpSound;
	delete buffer;
	delete attackSound;
}

void Music::JumpSound(void)
{
	if(this->jumpSound->getStatus() != 2)
	{
		this->jumpSound->play();

	}
	 
}



void Music::BackGroundMusic(void)
{
	if (!musicBack->openFromFile("Ressources/song1.ogg"))
	{

	}
	else
	{
		musicBack->play();
		musicBack->setLoop(true);
	}
	
}