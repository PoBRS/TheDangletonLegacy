#include "stdafx.h"
#include "ScoreReader.h"
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
/**
	Consctructeur de ScoreReader. Va lire un fichier de score sous le format score;nom;\nscore;joueur;
*/
ScoreReader::ScoreReader(std::string _pathToFile)
{
	this->scoreVector = new std::vector<std::pair<unsigned int, std::string>>;
	this->pathToFile = _pathToFile;
}

ScoreReader::~ScoreReader(void)
{
	delete this->scoreVector;
}

/**
	Fonction qui va lire le fichier de score et va ajouter ces entrée dans le vecteur.
*/
void ScoreReader::readFile(void)
{
	this->scoreVector->clear();
	this->scoreVector->push_back(std::make_pair(0,"N/A"));
	std::ifstream scoreFileStream;
	scoreFileStream.open(this->pathToFile);
	if (scoreFileStream.is_open())
	{
		while(scoreFileStream)
		{
			if(scoreFileStream != NULL)
			{
				std::string readLine = "";
				getline(scoreFileStream,readLine);
				if (readLine != "")
				{
					std::stringstream readLineStream(readLine);
					std::stringstream lineElementStream(readLine);

					std::string name;
					std::string scoreString;

					std::getline(lineElementStream,name,';');
					std::getline(lineElementStream,scoreString,';');
					unsigned int score = atoi(scoreString.c_str());

					this->scoreVector->push_back(std::make_pair(score,name));
				}
			}
		}
		scoreFileStream.close();
	}
}

/**
	Fonction qui va ajouter un score au fichier des scores.
	@param[in] _score le score du joueur.
	@param[in] _name Le nom du joueur.
	@return true si le joueur a pu être ajouté, sinon false.
*/
bool ScoreReader::AddNewScore(const unsigned int _score,const std::string _name)
{
	std::ofstream scoreFileStream;
	scoreFileStream.open(this->pathToFile, std::ios::app);
	if (scoreFileStream.is_open())
	{
		scoreFileStream << _name << ";" << std::to_string(_score) << ";" << std::endl;
		scoreFileStream.close();
		return true;
	}
	return false;
}

/**
	Fonction qui renvoie le vecteur de score trié selon le meilleur score en premier.
	@return Le vecteur de score trié.
	@see readFile
*/
std::vector<std::pair<unsigned int, std::string>>* ScoreReader::getScoreVector(void)
{
	// From http://stackoverflow.com/questions/279854/how-do-i-sort-a-vector-of-pairs-based-on-the-second-element-of-the-pair
	struct sort_pair
	{
		bool operator()(const std::pair<int,std::string>& _left,const  std::pair<int,std::string>& _right )
		{
			return _left.first > _right.first;
		}
	};
	this->readFile();
	std::sort(this->scoreVector->begin(), this->scoreVector->end(), sort_pair());
	return this->scoreVector;
}