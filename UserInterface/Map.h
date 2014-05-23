#include <vector>
#include "MapDisplay.h"
#include "../DataDeposit/TextFileReader.h"
#include <SFML\Graphics.hpp>
class Map
{
public:
	Map(std::string _mapFilePath);
	~Map(void);
	void displayMap(sf::RenderWindow& _mWindow);
	MapTile** mapTileArray;
	std::vector<int> GetpositionXCollectible(void);
	std::vector<int> GetpositionYCollectible(void);
	std::vector<int> GetpositionXEnemy(void);
	std::vector<int> GetpositionYEnemy(void);
	std::vector<MapTile*> mapTileVector;
private:
	TextFileReader* reader;
	char** mapDispositionArray;
	std::vector<MapDisplay*> mapDisplay;
	void Map::BuildMapArray(std::string _mapFilePath);
	void SetEnemy(int _x, int _y);
	void SetCollectible(int _x, int _y);
	std::vector<int> positionXEnemy;
	std::vector<int> positionYEnemy;
	std::vector<int> positionXCollectible;
	std::vector<int> positionYCollectible;
};

