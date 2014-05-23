#ifndef _SCORE_READER_H
#define _SCORE_READER_H

#include <string>
#include <vector>

class ScoreReader
{
public:
	ScoreReader(std::string _pathToFile);
	~ScoreReader(void);
	bool AddNewScore(const unsigned int _score, const std::string _name);
	std::vector<std::pair<unsigned int, std::string>>* getScoreVector(void);
private:
	void readFile(void);
	std::vector<std::pair<unsigned int, std::string>>* scoreVector;
	std::string pathToFile;
};

#endif