#include "CText.h"
#include <stdlib.h>

CText::CText(string InputFileName, string stopWordFilePATH,string PathToTempFile, int SegmentSize, int NgramSize)
	: miSegmentSize(SegmentSize), miNgramSize(NgramSize), mfInputFile(InputFileName), mfStopWordFile(stopWordFilePATH)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		Global_PathToTempFiles = mPathToTempFiles = PathToTempFile;
		vector<string> TempNgramSeg;
		mfInputFile = InputFileName;
		mfStopWordFile = stopWordFilePATH;
		readStopWordFile();
		RemoveStopWordList();
		DivideTextIntoSegments();

		//in this step - all Segments NGrams created , mvDictionary is fully updated 
		// time to build CFM and SP's for each segment by DSeg.BuildSegmentCFM(vector<string>& vDictionary);
		for each (auto TempSeg in mvSegments)
		{
			//TempNgramSeg = TempSeg->ReadNgramDataFromFile();
			TempSeg->BuildSegmentCFMandSP(mvDictionary);
		}

		//in this step - all CFM's and SP's created for each segment.
		// time to build TM(Transition Matrix) for each segment except the last 
		// implement by CAlgorithms::BuildTmBetweenSPs , and save matrix file in DSeg.msSegmentTmFileName
		for (int i = 0; i < mvSegments.size() - 1; ++i)
		{
			mvSegments[i]->CalcTransitionMatrix(mvSegments[i + 1]->GetSegmentSPfileName());
		}

		//in this step - all TM's created 
		// time to build TM(Transition Matrix) for each segment except the last 
		// implement by BuildTmeas() , and save matrix file name in msTmeasFileName
		//checkinh mvSegments.size() > 2 - for verify there is any TM between 2 segments
		if (mvSegments.size() > 2)
			BuildTmeas();

		//in this step - Tmeas created
		// time to build set approximation error between each two segment except the last 
		// implement by SetApproximationErrorBetweenSegments() , and save approximation error in mmSegmentsApproximationError 
		SetApproximationErrorBetweenSegments();
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CText::readStopWordFile(void)
{
	ifstream StopWordFile;
	
	if (!mfInputFile.empty())
	{
		StopWordFile.open(mfStopWordFile);
		if (!StopWordFile.is_open())
		{
			CLogger::GetLogger()->Log("Error While trying ot read stopWords list");
			exit(1);
		}

		string temp;
		while (!StopWordFile.eof())
		{
			StopWordFile >> temp;
			/*Avoid  stop words removal when they are part of another word*/
			temp.append(" ");
			temp.insert(0, " ");
			mvStopWordList.push_back(temp);
		}
		StopWordFile.close();

		//if (!stopWordList.empty())/*remove stopwords  from file*/
		//{
		//	fileManager::RemoveStopWordList(fileNamePATH);
		//}

		CLogger::GetLogger()->Log("Stop words list file created succesfully");
	}
}


CText::~CText()
{
	CError Err(""); Err.AddID("CText", __FUNCTION__);
	CLogger::GetLogger()->Log(Err.GetErrMsg());
}

/*RemoveStopWordList:
* The function using :
*       mvStopWordList-contains stopwords List that have been readed from stopwords input file.
*       mfInputFile-should be loaded before function call
* output:
*		mfInputFileWithoutstopWord -input without the stopwords list
*General:
*		The function reads all the input file deleting the stopwords (if exist)
*		and writing the new data into a new file named as the input file with
*		NEW_FILE_NAME_AFTER_STOP_WORDS_REM extension.
*		At the end of the run the function save the new file name as mfInputFileWithoutstopWord.
*/
void CText::RemoveStopWordList(void)
{
#define NEW_FILE_NAME_AFTER_STOP_WORDS_REM "_withoutStopWord.txt"

	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());


		std::ifstream readStream;
		ofstream writeStream(mfInputFile + NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
		std::string lineData;
		std::vector<char*> fileData;
		readStream.open(mfInputFile);

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
				for (int i = 0; i < mvStopWordList.size(); i++)
				{
					removeSubstrs(lineData, mvStopWordList[i]);
				}
				writeStream << lineData << endl;
			}
		}

		CLogger::GetLogger()->Log("A new File Created ,named %s%s ", mfInputFile.c_str(), NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
		readStream.close();
		writeStream.close();

		/*Set the new file as the input file*/
		// save TextWithoutstopWord to mfInputFileWithoutstopWord
		mfInputFileWithoutstopWord = mfInputFile + NEW_FILE_NAME_AFTER_STOP_WORDS_REM;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}


//creating the mvSegments (Segments vector) by :
//  call CDynamicSystemSegment constructor:
//	CDynamicSystemSegment(string& SegmentData, int NgramSize, int SegmentSize, vector<string>& vDictionary);
//  split the text to segments according to SegmentSize.
void CText::DivideTextIntoSegments(void)
{
	// miSegmentSize && mfInputFileWithoutstopWord && mvDictionary && mvSegments - לא לשכוח להשתמש ב

	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		//string temp("asd");
		//CSegment TempSeg(temp, 3, mvDictionary);
		int available=0;
		string reader, block;
		int readerSize;
		int currentBlockSize = miSegmentSize;
		int counter = 0;
		ifstream inputFile(mfInputFileWithoutstopWord);
		if (!inputFile.is_open())
		{
			CLogger::GetLogger()->Log("Cant open mfInputFileWithoutstopWord in DivideTextIntoSegments()-exit(1)");
			exit(1);
		}
		while (!inputFile.eof())
		{
			counter++;
			if (reader.size() == 0)
				std::getline(inputFile, reader);

			readerSize = (int)reader.size();
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
				mvSegments.push_back(make_shared<CDynamicSystemSegment> (block, miNgramSize, mPathToTempFiles, mvDictionary));
				block.erase();
				readerSize -= currentBlockSize;
				reader.erase(0, currentBlockSize);
				currentBlockSize = miSegmentSize;

			}
		}

		inputFile.close();


	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

// scan each segment except the last , calculate Tmeas matrix and save it in msTmeasFileName
void CText::BuildTmeas(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		// implementation here
		arma::mat Res, Temp;
		Temp.load(mvSegments[0]->GetSegmentTmFileName());
		Res.set_size(Temp.n_rows, Temp.n_rows);
		Res.zeros();
		for (int i = 0; i < mvSegments.size() - 1; ++i)
		{
			Temp.load( mvSegments[i]->GetSegmentTmFileName() );
			Res = Res + Temp;
		}
		Res /= (mvSegments.size() - 1);

		string filename = mPathToTempFiles;
		filename.append("\\TMeasMatrix");
		Res.save(filename, arma::arma_ascii);
		msTmeasMatricesfileName = filename;

		CLogger::GetLogger()->Log("TMeas created successfully");
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

// scan each segment except the last , calculate approximation error between each two segment except the last 
// and save it in DSeg.mfApproximationError
// also fill mmSegmentsApproximationError 
void CText::SetApproximationErrorBetweenSegments(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		arma::mat TMmeas, T1, T2;
		TMmeas.load(msTmeasMatricesfileName);
		for (int i = 0; i < mvSegments.size() - 2; ++i)
		{
			T1.load(mvSegments[i]->GetSegmentTmFileName());
			T2.load(mvSegments[i+1]->GetSegmentTmFileName());
			double res = norm(T1*TMmeas - T2);
			res /= norm(T1);
			mvSegments[i]->SetApproximationError(res);
			// fill correct double vector with Approximation Errors
			mmSegmentsApproximationError[i] = res;
		}
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

map<int, double> CText::GetSegmentsApproximationErrorMap(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		return mmSegmentsApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}
