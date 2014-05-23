#include <SFML/Audio.hpp>
class Music
{
public:
	Music(void);
	~Music(void);
	void JumpSound(void);
	void AttackSound(void);
	void BackGroundMusic(void);
	sf::Sound* GetSound(void);

private:
	
	sf::SoundBuffer *buffer;
	sf::Sound *jumpSound;
	sf::Sound *attackSound;
	sf::Music *musicBack;
};
