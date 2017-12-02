#include "fileManager.h"



fileManager::fileManager()
{
	CLogger::GetLogger()->Log("file Manager Created");
}

/*The c'tor gets the  full path  to the file as a string  and have the ability 
to read the file ,split to anagram and create the matrixes*/
fileManager::fileManager(string fileNamePATH ,string stopWordFilePATH)
{
	
	CLogger::GetLogger()->Log("Open input file for reading");
	inputFile.open(fileNamePATH);
	if (! inputFile.is_open())
	{
		CLogger::GetLogger()->Log("Cannot open input file");
		exit(1);
	}

	

	/*read stopword list and save them in a List*/
	if (! stopWordFilePATH.empty())
	{
		stopWordFile.open(stopWordFilePATH);
		if (!stopWordFile.is_open())
		{
			CLogger::GetLogger()->Log("Error While trying ot read stopWords list");
			exit(1);
		}

		string temp;
		while (!stopWordFile.eof())
		{
			stopWordFile >> temp;
			stopWordList.push_back(temp);
		}
		if (!stopWordList.empty())/*remove stopwords  from file*/
		{
			
			fileManager::RemoveStopWordList(stopWordFilePATH);
		}

		CLogger::GetLogger()->Log("Stop words list were created succesfully");
	}

}


void fileManager::readFile(int segSize)
{
	string reader , block;
	int size;
	int currentBlockSize = segSize;
	while (! inputFile.eof())
	{
		inputFile >> reader;
		size = reader.size();
		if (reader.empty())
			continue;
		try {
			if (currentBlockSize - size > 0)
			{
				block += reader;
				currentBlockSize -= size;
			}
			else {
				/*insert  according to free size left */
				block += reader.substr(0, currentBlockSize);
				textBlocks.push_back(block);
				block.erase();
				block += reader.substr(currentBlockSize, size - currentBlockSize);
				currentBlockSize = segSize - block.size();
			}
		}
		catch (exception e)
		{
			cout << reader << endl;
			

			return;
		}
	}
}



void fileManager::createAnagramMatrix(int NgramSize)
{
	Ngrams.empty();
	int segSeize ,jBlockOffset,iBlock = 0;
	string Curr_Block,tempNGram;
	vector <string> raw;
	while (!textBlocks[iBlock].empty())
	{
		Curr_Block = textBlocks[iBlock++];
		segSeize = Curr_Block.size();
		jBlockOffset = 0;
		while (Curr_Block[jBlockOffset]  &&  Curr_Block[jBlockOffset + NgramSize])
		{

			tempNGram = Curr_Block.substr(jBlockOffset, NgramSize);
			raw.push_back(tempNGram);
			jBlockOffset++;
		}
		/*Igonre the block leftover */
		Ngrams.push_back(raw);
		raw.clear();
	}
	CLogger::GetLogger()->Log("Block were Splited into Ngrams - createAnagramMatrix() Finshed");
}

void fileManager::RemoveStopWordList(string fileNamePATH)
{
	std::ifstream readStream;
	std::string lineData;
	char * lineString;
	std::vector<char*> fileData;
	readStream.open(fileNamePATH);
	if (!readStream.is_open())
	{
		CLogger::GetLogger()->Log("Cant open file for emoving stop words -exit(1)");
		exit(1);
	}
	while (!readStream.eof())
	{
		std::getline(readStream, lineData);
		if (!lineData.empty())
			for (int i = 0; i < stopWordList.size(); i++)
			{

				/*Check if lineData contain at list won sub str of the list*/
				//if(lineData.find(stopWordList.pop_back()))

			}
	}
}




fileManager::~fileManager()
{
	CLogger::GetLogger()->Log("File Manager D'tor");
}
