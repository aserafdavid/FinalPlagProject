#pragma once
#include <iostream>
#include "string.h"
#include <fstream>
#include <vector>
#include "Logger.h"

using namespace std;

class fileManager
{
	
public:
	//static bool isFileWithoutStopWordsListCreated;
	fileManager(string fileNameInput,string stopWordFilePATH);
	void readFile(int segSize);
	fileManager::fileManager();
	~fileManager();
	void createAnagramMatrix(int NgramSize);
	void RemoveStopWordList(string fileNamePATH);

private:
	ifstream inputFile;
	ifstream stopWordFile;
	vector<string> stopWordList;
	vector <string> textBlocks;
	vector <vector<string>> Ngrams;
	
};

