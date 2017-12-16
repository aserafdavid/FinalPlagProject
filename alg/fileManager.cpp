
#include "fileManager.h"
#include <direct.h>
#include <windows.h>

#define NEW_FILE_NAME_AFTER_STOP_WORDS_REM "_withoutStopWord.txt"

fileManager::fileManager()
{
	CLogger::GetLogger()->Log("file Manager Created ");
}

/*The c'tor gets the  full path  to the file as a string  and have the ability
to read the file ,split to anagram and create the matrixes*/
fileManager::fileManager(string fileNamePATH, string stopWordFilePATH)
{

	CLogger::GetLogger()->Log("Open input file for reading");
	inputFile.open(fileNamePATH);
	if (!inputFile.is_open())
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
	int readerSize;
	int currentBlockSize = segSize;
	int counter = 0;
	while (!inputFile.eof())
	{
		counter++;
		if (reader.size() == 0)
			std::getline(inputFile, reader);

		readerSize =(int) reader.size();
		if (reader.empty())
			continue;


		if (currentBlockSize > readerSize)
		{/*All reader should be inserted into block*/
			block += reader;
			currentBlockSize -= readerSize;
			reader.erase(0, readerSize);
		}
		else {
			/*Insert according to currentBlockSize reader size wouldn't bw empty after*/
			block += reader.substr(0, currentBlockSize);
			textBlocks.push_back(block);
			block.erase();
			readerSize -= currentBlockSize;
			reader.erase(0, currentBlockSize);
			currentBlockSize = segSize;

		}
	}
	/*Test All Blocks Size fo*/
	for each (string block in textBlocks)
	{
		if (block.size() != segSize)
		{
			CLogger::GetLogger()->Log("The Creation of he Blocks are unaccurate ,There is atleast one block that is size is diffrent from segSize ->check readFile() function");
		}
	}


}

static bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}


/*Double "Slash" for example ""c:\\CFM's\\*.txt"" */
static void DeleteAllFilesInFolder(string path)
{
	std::string command = "del /Q ";
	system(command.append(path).c_str());
}

static arma::mat Create_CFM(const vector <string> NgramSeg, vector <string>* dictionary)
{
	static int counter = 0;

	if (!dirExists("/CFM's"))
		_mkdir("/CFM's");
	else
		DeleteAllFilesInFolder("c:\\CFM's\\*.txt");

	arma::mat segCFM(dictionary->size(), NgramSeg.size());
	segCFM.fill(0);
	for (int i = 0; i < NgramSeg.size(); i++)
	{
		//size_t pos = NgramSeg[i] - dictionary->begin();
		auto  pos = find(dictionary->begin(), dictionary->end(), NgramSeg[i]) - dictionary->begin();
		if (pos >= (int)dictionary->size())
		{
			CLogger::GetLogger()->Log("There is an Ngram that exist in seg and doesn't exist in dictionary. found in Create_CFM()--> aborting");
			exit(1);
		}
		if (i == 0)
		{
			segCFM(pos, i)++;
		}
		else {

			segCFM.col(i) = segCFM.col(i - 1);/*copy last coloumn to the current one*/
			segCFM(pos, i)++;

		}
	}
	string filename = "/CFM's/segCFM" + std::to_string(counter++) + ".txt";
	segCFM.save(filename, arma::arma_ascii);
	//segCFM.load(filename);
	//arma::mat G;
	//G.load(filename);

	return segCFM;

}

void fileManager::createAnagramMatrix(int NgramSize)
{
	Ngrams.empty();
	int segSeize, jBlockOffset, iBlock = 0;
	string Curr_Block, tempNGram;
	vector <string> raw;
	for (int i = 0; i < textBlocks.size(); i++)// (!textBlocks[iBlock].empty())
	{

		Curr_Block = textBlocks[iBlock++];
		segSeize =(int) Curr_Block.size();
		jBlockOffset = 0;
		while (Curr_Block[jBlockOffset] && Curr_Block[jBlockOffset + NgramSize])
		{

			tempNGram = Curr_Block.substr(jBlockOffset, NgramSize);
			if (!(std::find(dictionary.begin(), dictionary.end(), tempNGram) != dictionary.end()))
				dictionary.push_back(tempNGram);

			raw.push_back(tempNGram);
			jBlockOffset++;
		}
		/*Igonre the block leftover */
		Ngrams.push_back(raw);
		raw.clear();
	}
	CLogger::GetLogger()->Log("Block were Splited into Ngrams - createAnagramMatrix() Finished Succesfully");
}

static void removeSubstrs(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p); i != string::npos; i = s.find(p))
		s.erase(i, n);
}

void fileManager::RemoveStopWordList(string fileNamePATH)
{
	std::ifstream readStream;
	ofstream writeStream(fileNamePATH + NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
	std::string lineData;
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
			writeStream << lineData << endl;
		}
	}

	CLogger::GetLogger()->Log("A new File Created ,named %s%s ", fileNamePATH.c_str(), NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
	readStream.close();
	writeStream.close();

}

void fileManager::CreateAllCFMsMatrixes()
{
	static int count;
	arma::mat CFMS;
	for each(vector<string> NSeg in Ngrams)
	{
		Create_CFM(NSeg, &dictionary);
	}
}

fileManager::~fileManager()
{
	CLogger::GetLogger()->Log("File Manager D'tor");
}
