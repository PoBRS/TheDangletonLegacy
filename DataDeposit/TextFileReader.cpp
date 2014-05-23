//http://www.cplusplus.com/forum/general/1690/
#include "stdafx.h"
#include "TextFileReader.h"
#include <fstream>

TextFileReader::TextFileReader()
{

}

TextFileReader::~TextFileReader()
{

		for (int i = 0; i < 10 ; ++i)
		{
			delete [] carray[i];
		}
 

		delete [] carray;
	
}

char** TextFileReader::ReadInCharArray(std::string mapFilePath,int maximumMapWidth,int maximumMapHeight)
{

	      // Array to read into (at most 100 characters + ASCIIZ)
	size_t line = 0;   // Number of characters read so far (used to index array)
	size_t column = 0;

	this->carray = new char *[maximumMapHeight];
	for(int column = 0; column < maximumMapHeight; column++)
		carray[column] = new char[maximumMapWidth];

	std::ifstream input(mapFilePath);  //  The input file
	if (input.is_open())
	{
		while(input)
		{
			if(input != NULL)
			{
				input >> carray[ line ][ column ];
				column++;
				if(input.peek() == '\n') 
				{       
					++line;                  // Move to next line
					column = 0;                //  And don't forget to reset column!
				}
			}
			else
			{
				carray[line][column] = 0;
			}
		}
	}
	input.close();
	return carray;

}