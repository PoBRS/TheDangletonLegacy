#include <SFML/Graphics.hpp>
#include "MapTile.h"
class MapDisplay
{
public:
	MapDisplay(std::string _filePath, MapTile& _linkedMapTile);
	~MapDisplay(void);
	sf::Sprite getSprite(void);
private:
	
	sf::Texture texture;
		sf::Sprite sprite;
};