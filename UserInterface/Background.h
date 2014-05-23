#include <SFML/Graphics.hpp>
class Background
{
public:
	Background(std::string _filePath);
	~Background(void);
	sf::Sprite getSprite(void);
private:
	
	sf::Texture texture;
	sf::Sprite sprite;
};