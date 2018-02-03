#include "CText.h"
#include <stdlib.h>
#include <thread>
#include "main.h"
#include <locale>

CText::CText(string InputFileName, string stopWordFilePATH,string PathToTempFile, AprroachModel Aprroach,
				int SegmentSize, int NgramSize, int ClusterNumberRequested)
	: miSegmentSize(SegmentSize), miNgramSize(NgramSize), mfInputFile(InputFileName), mfStopWordFile(stopWordFilePATH), meAprroach(Aprroach)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		Global_PathToTempFiles = mPathToTempFiles = PathToTempFile;
		miClusterNumberRequested = ClusterNumberRequested;
		vector<string> TempNgramSeg;
		readStopWordFile();
		RemoveStopWordList();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(OmitStopWordsStepFinished);
		TerminateIfNeeds();

		//*CurrStatePtr = OmitStopWordsStepFinished;
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		DivideTextIntoSegments();
		UpdateStates(DevideTextToSegStepFinished);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(ExtractNgramsStepFinished);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(BuildVocStepFinished);
		TerminateIfNeeds();

		//in this step - all Segments NGrams created , mvDictionary is fully updated 
		// time to build CFM and SP's for each segment by DSeg.BuildSegmentCFM(vector<string>& vDictionary);

		miConcurrentThreadsNumber = std::thread::hardware_concurrency();
		cout << "hardware_concurrency() = " << miConcurrentThreadsNumber << endl;
		std::thread* t;
		if (miConcurrentThreadsNumber >= MAXT)
		{
			t= new std::thread[MAXT];
			miConcurrentThreadsNumber = MAXT;
		}
		else if (miConcurrentThreadsNumber >= MIDHT)
		{
			t = new std::thread[MIDHT];
			miConcurrentThreadsNumber = MIDHT;
		}
		else if (miConcurrentThreadsNumber >= MIDLT)
		{
			t = new std::thread[MIDLT];
			miConcurrentThreadsNumber = MIDLT;
		}
		else
		{
			t = new std::thread[MINT];
			miConcurrentThreadsNumber = MINT;
		}

		/*fill the correct segments vector according to Aprroach Model*/
		if (DS_Aprroach == meAprroach || Both_Aprroaches == meAprroach)
		{
			for (int i = 0; i < miConcurrentThreadsNumber; ++i)
			{
				t[i] = std::thread (std::bind(&CText::BuildSegmentCFMandSPThreadDS,this));
			}

			for (int i = 0; i < miConcurrentThreadsNumber; ++i)
			{
				t[i].join();
			}
			//*CurrStatePtr = ExtractNgramsStepFinished;
			//*CurrStatePtr = BuildVocStepFinished;

			UpdateStates(BuldCFMsStepFinished);
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			UpdateStates(BuildSPsStepFinished);
			TerminateIfNeeds();

			CompleteDsProcess();
			TerminateIfNeeds();
		}
		else if (CL_Aprroach == meAprroach)
		{
			for (int i = 0; i < miConcurrentThreadsNumber; ++i)
			{
				t[i] = std::thread(std::bind(&CText::BuildSegmentCFMandSPThreadCL, this));
			}

			for (int i = 0; i < miConcurrentThreadsNumber; ++i)
			{
				t[i].join();
			}
			CompleteClProcess();
			TerminateIfNeeds();
		}
		if (Both_Aprroaches == meAprroach)
		{
			// acctually only DS_Aprroach happened till now, 
			// copy relevant data to mvClSegments (SP data) for all the segments 
			// and continue with CL process.
			for (int i = 0; i < mvDsSegments.size() ; ++i)
			{
				const CClusteredSegment ClSeg = *mvDsSegments[i];
				mvClSegments.push_back(make_shared<CClusteredSegment>(ClSeg));
			}
			CompleteClProcess();
			TerminateIfNeeds();
		}

		

	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CText::BuildSegmentCFMandSPThreadDS()
{
	for (int i = miInitForThreads++ ; i < mvDsSegments.size(); i += miConcurrentThreadsNumber)
	{
		mvDsSegments[i]->BuildSegmentCFMandSP(mvDictionary);
		TerminateIfNeeds();
	}
}

void CText::BuildSegmentCFMandSPThreadCL()
{
	for (int i = miInitForThreads++; i < mvClSegments.size(); i += miConcurrentThreadsNumber)
	{
		mvClSegments[i]->BuildSegmentCFMandSP(mvDictionary);
	}
}

void CText::readStopWordFile(void)
{
	ifstream StopWordFile;
	
	if (!mfInputFile.empty() && mfStopWordFile!="EMPTY")
	{
		string path = mPathToTempFiles;
		string ext = "tempFiles";
		path = path.substr(0, path.size() - 30);

		if (mfStopWordFile == "ACADEMIC")
		{
			path.append("\\PlagiarismDetection\\StopWordsAcademic.txt");
			StopWordFile.open(path);
		}
		else if (mfStopWordFile == "LITERATURE")
		{
			path.append("\\PlagiarismDetection\\StopWordsLitrearture.txt");
			StopWordFile.open(path);
		}
		else
		{
			StopWordFile.open(mfStopWordFile);
		}

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

		CLogger::GetLogger()->Log("Stop words list file created succesfully");
	}
}


CText::~CText()
{
	//CError Err(""); Err.AddID("CText", __FUNCTION__);
	//CLogger::GetLogger()->Log(Err.GetErrMsg());
}

void ReplaceStringInPlace(std::string& subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
	string tempSubject = subject;

	
	std::transform(tempSubject.begin(), tempSubject.end(), tempSubject.begin(), ::tolower);

    while((pos = tempSubject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
		 tempSubject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
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
		//CError Err(""); Err.AddID("CText", __FUNCTION__);
		//CLogger::GetLogger()->Log(Err.GetErrMsg());
		
		if (mfStopWordFile == "EMPTY")
		{
			mfInputFileWithoutstopWord = mfInputFile;
		}
		else
		{
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
						string res;
						ReplaceStringInPlace(lineData, mvStopWordList[i], " ");
						
					}
					writeStream << lineData << endl;
				}
			}

			//CLogger::GetLogger()->Log("A new File Created ,named %s%s ", mfInputFile.c_str(), NEW_FILE_NAME_AFTER_STOP_WORDS_REM);
			readStream.close();
			writeStream.close();

			/*Set the new file as the input file*/
			// save TextWithoutstopWord to mfInputFileWithoutstopWord
			mfInputFileWithoutstopWord = mfInputFile + NEW_FILE_NAME_AFTER_STOP_WORDS_REM;
		}	
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
		//CLogger::GetLogger()->Log(Err.GetErrMsg());

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

				/*fill the correct segments vector according to Aprroach Model*/
				if (DS_Aprroach == meAprroach || Both_Aprroaches == meAprroach)
				{
					mvDsSegments.push_back(make_shared<CDynamicSystemSegment>(block, miNgramSize, mPathToTempFiles, mvDictionary));
				}
				else if (CL_Aprroach == meAprroach)
				{
					mvClSegments.push_back(make_shared<CClusteredSegment>(block, miNgramSize, mPathToTempFiles, mvDictionary));
				}
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

void CText::CompleteDsProcess(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		//in this step - all CFM's and SP's created for each segment.
		// time to build TM(Transition Matrix) for each segment except the last 
		// implement by CAlgorithms::BuildTmBetweenSPs , and save matrix file in DSeg.msSegmentTmFileName
		for (int i = 0; i < mvDsSegments.size() - 1; ++i)
		{
			mvDsSegments[i]->CalcTransitionMatrix(mvDsSegments[i + 1]->GetSegmentSPfileName());
		}
		UpdateStates(BuildQsStepFinished);
		TerminateIfNeeds();

		//in this step - all TM's created 
		// time to build TM(Transition Matrix) for each segment except the last 
		// implement by BuildTmeas() , and save matrix file name in msTmeasFileName
		//checkinh mvSegments.size() > 2 - for verify there is any TM between 2 segments
		if (mvDsSegments.size() > 2)
			BuildTmeas();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		UpdateStates(CalcAQMeasureStepFinished);
		TerminateIfNeeds();


		//in this step - Tmeas created
		// time to build set approximation error between each two segment except the last 
		// implement by SetApproximationErrorBetweenSegments() , and save approximation error in mmSegmentsApproximationError 
		SetApproximationErrorBetweenSegments();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(CalcApproxMeasStepFinished);
		TerminateIfNeeds();

		CreateResultsFileForDS();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(ExamineResult);
		TerminateIfNeeds();

		// print Aproximation Errors
		cout << "Aproximation Errors by Segments:\n";
		map<int, double> ApproximationErrorMap = GetSegmentsApproximationErrorMap();
		cout << endl;
		for (std::map<int, double>::iterator it = ApproximationErrorMap.begin(); it != ApproximationErrorMap.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CText::CompleteClProcess(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		//in this step - all CFM's and SP's created for each segment.
		// time to calculate EV(eigen values) for each SP matrix by QR algorithm., then create EVM(eigen values matrix) -
		// unite of all  EV vectors from each segment's EV. 
		// implement by CClusteredSegment::CalcEV using CAlgorithms::RunQrAlg.
		arma::mat dummy;
		dummy.load(mvClSegments[0]->GetSegmentSPfileName() );

		mEVM.set_size(dummy.n_cols, mvClSegments.size());
		mEVM.zeros();

		for (int i = 0; i < mvClSegments.size() ; ++i)
		{
			mEVM.col(i) = mvClSegments[i]->CalcEV();
		}
		CLogger::GetLogger()->Log("EVM created successfully.");

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(EvmCreationFinished);
		TerminateIfNeeds();

		//in this step - EVM created.
		// time to call to Kmeas algorithm with EVM and CL_num as parameters and save all the clustering results.
		// CL_num - const number - 2..9
		// Then examine each Kmeas result by Silhouette algorithm, and choose the best Kmeas clusterization by Silhouette.
		// implement by CAlgorithms::FindBestClusterization, result save in mat means.
		pair<int ,map<int, int> > BestClustersMap;
		CAlgorithms::FindBestClusterization(mEVM, BestClustersMap, miClusterNumberRequested);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(ClusterizationFinished);
		TerminateIfNeeds();

		CreateResultsFileForCL(BestClustersMap);
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		UpdateStates(ExamineCLResult);
		TerminateIfNeeds();

		//print BestClustersMap
		cout << endl << "Number of clusters for Best Clusterization: " << BestClustersMap.first << endl;
		for (map<int,int>::iterator it = BestClustersMap.second.begin(); it != BestClustersMap.second.end(); ++it)
		{
			cout << "Seg " << it->first << " => " << it->second << endl;
		}
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CText::CreateResultsFileForDS(void)
{
	try 
	{
		ofstream ResFile;
		string DSpath = mPathToTempFiles;
		DSpath.append("\\Results\\DS_Results.txt");
		ResFile.open(DSpath);

		for (int i = 0; i < mvDsSegments.size() - 2; ++i)
		{
			ResFile << mvDsSegments[i]->GetApproximationError() << "\t";
			ResFile << mvDsSegments[i]->GetSegmentData() << endl;
		}
		ResFile << "\t" << mvDsSegments[mvDsSegments.size() - 1]->GetSegmentData() ;
		ResFile.close();
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CText::CreateResultsFileForCL(pair<int, map<int, int> > ClustersPair)
{
	try 
	{
		ofstream ResFile;
		string DSpath = mPathToTempFiles;
		DSpath.append("\\Results\\CL_Results.txt");
		ResFile.open(DSpath);

		for (int i = 0; i < mvClSegments.size() ; ++i)
		{
			ResFile << ClustersPair.second[i] << "\t";
			ResFile << mvClSegments[i]->GetSegmentData() << endl;
		}
		ResFile.close();
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
		//CError Err(""); Err.AddID("CText", __FUNCTION__);
		//CLogger::GetLogger()->Log(Err.GetErrMsg());

		// implementation here
		arma::mat Res, Temp;
		Temp.load(mvDsSegments[0]->GetSegmentTmFileName());
		Res.set_size(Temp.n_rows, Temp.n_rows);
		Res.zeros();
		for (int i = 0; i < mvDsSegments.size() - 1; ++i)
		{
			Temp.load(mvDsSegments[i]->GetSegmentTmFileName() );
			Res = Res + Temp;
		}
		Res /= (mvDsSegments.size() - 1);

		string filename = mPathToTempFiles;
		filename.append("\\TMeasMatrix.txt");
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
		//CError Err(""); Err.AddID("CText", __FUNCTION__);
		//CLogger::GetLogger()->Log(Err.GetErrMsg());

		arma::mat TMmeas, T1, T2;
		TMmeas.load(msTmeasMatricesfileName);
		for (int i = 0; i < mvDsSegments.size() - 2; ++i)
		{
			T1.load(mvDsSegments[i]->GetSegmentTmFileName());
			T2.load(mvDsSegments[i+1]->GetSegmentTmFileName());
			double res = norm(T1*TMmeas - T2);
			res /= norm(T1);
			res /= pow(10, 12);/*Normalize Values*/
			mvDsSegments[i]->SetApproximationError(res);
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
		//CError Err(""); Err.AddID("CText", __FUNCTION__);
		//CLogger::GetLogger()->Log(Err.GetErrMsg());

		return mmSegmentsApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}
