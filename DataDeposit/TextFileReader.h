
#pragma once
#include <string>

class TextFileReader
{
public:
	TextFileReader();
	~TextFileReader();
	char** ReadInCharArray(std::string mapFilePath,const int maximumMapWidth,const int maximumMapHeight);
private:
	char** carray;
	
};
