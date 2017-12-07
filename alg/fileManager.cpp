#include "fileManager.h"

#define NEW_FILE_NAME_AFTER_STOP_WORDS_REM "_withoutStopWord.txt"

fileManager::fileManager()
{
	//isFileWithoutStopWordsListCreated = false;
	CLogger::GetLogger()->Log("file Manager Created ");
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
	if (!stopWordFilePATH.empty())
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
			/*Avoid  stop words removal when they are part of another word*/
			temp.append(" ");
			temp.insert(0, " ");
			stopWordList.push_back(temp);
		}
		stopWordFile.close();

		if (!stopWordList.empty())/*remove stopwords  from file*/
		{

			fileManager::RemoveStopWordList(fileNamePATH);
			//isFileWithoutStopWordsListCreated = true;
			
		}

		CLogger::GetLogger()->Log("Stop words list file created succesfully");
	}
	inputFile.close();/*Set input file to be the file without the stop words.*/
	inputFile.open(fileNamePATH + NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
	if (!inputFile.is_open())
	{
		CLogger::GetLogger()->Log("failed to open the new input file without the stop words list");
		exit(1);
	}

}

void fileManager::readFile(int segSize)
{
	string reader, block;
	int size;
	int currentBlockSize = segSize;
	int counter=0;
	while (!inputFile.eof())
	{
		counter++;
		if (counter == 3)
		{
			cout << "stop here";
		}
		std::getline(inputFile, reader);
		//inputFile >> reader;
		size = reader.size();
		if (reader.empty())
			continue;
		try {
			if (currentBlockSize > size)
			{
				block += reader;
				currentBlockSize -= size;
			}
			else {
				/*insert  according to free size left */
				size = reader.size();
				while (size > segSize)
				{
					block += reader.substr(0, currentBlockSize);
					textBlocks.push_back(block);
					block.erase();
					size -= currentBlockSize;
					reader.erase(0, currentBlockSize);
					currentBlockSize = segSize;// -block.size();
					
				}
				block += reader.substr(0, size);
				currentBlockSize -= size;
				textBlocks.push_back(block);
				block.erase();

			}
			
			
		}
		catch (exception e)
		{
			CLogger::GetLogger()->Log("Excepton were cought wile reading file at the %d cycle in the loop", counter);
			return;
		}
	}
}



void fileManager::createAnagramMatrix(int NgramSize)
{
	Ngrams.empty();
	int segSeize, jBlockOffset, iBlock = 0;
	string Curr_Block, tempNGram;
	vector <string> raw;
	while (!textBlocks[iBlock].empty())
	{
		Curr_Block = textBlocks[iBlock++];
		segSeize = Curr_Block.size();
		jBlockOffset = 0;
		while (Curr_Block[jBlockOffset] && Curr_Block[jBlockOffset + NgramSize])
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

void removeSubstrs(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p) ; i != string::npos ; i = s.find(p))
		s.erase(i, n);
}


void fileManager::RemoveStopWordList(string fileNamePATH)
{
	std::ifstream readStream;
	std:ofstream writeStream(fileNamePATH + NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
	std::string lineData;
	char * lineString;
	std::vector<char*> fileData;
	readStream.open(fileNamePATH);

	if (!readStream.is_open() || !writeStream.is_open())
	{
		CLogger::GetLogger()->Log("Cant open file for removing stop words -exit(1)");
		exit(1);
	}
	while (!readStream.eof())
	{
		std::getline(readStream, lineData);
		if (!lineData.empty())
		{
			for (int i = 0; i < stopWordList.size(); i++)
			{
				removeSubstrs(lineData, stopWordList[i]);
			}
			writeStream << lineData <<	endl;
		}
	}

	CLogger::GetLogger()->Log ( "A new File Created ,named %s%s ",fileNamePATH, NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
	readStream.close();
	writeStream.close();

}




fileManager::~fileManager()
{
	CLogger::GetLogger()->Log("File Manager D'tor");
}
