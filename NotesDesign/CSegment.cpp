
#include "CSegment.h"

#ifndef _Algorithms_h_
#include "CAlgorithms.h"

/*in this default c'tor should create the file and update the Dictionary*/
CSegment::CSegment(CSegment & origin)
{

}

//1) Create Ngrams From Segment according to NgramSize , update vDictionary accordingly.
//2) finnaly Save vSegmentNgrams to mfSegmentNgramsfile 
CSegment::CSegment(string& SegmentData, int NgramSize, vector<string>& vDictionary)
//: msSegmentData(SegmentData)
{
#define NgramsFilesPath "tempFiles/SegNgrams/"
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		/********************************/
		static int counter = 0;
		miSegmentNumber = counter++;
		miSegSize = SegmentData.size();
		miNgramSize = NgramSize;
		msSegmentData = SegmentData;

		mvSegmentNgrams.empty();
		int segSeize, jBlockOffset, iBlock = 0;
		string  tempNGram;
		vector <string> raw;

		segSeize = (int)SegmentData.size();
		jBlockOffset = 0;
		while (SegmentData[jBlockOffset] && SegmentData[jBlockOffset + NgramSize])
		{

			tempNGram = SegmentData.substr(jBlockOffset, NgramSize);
			if (!(std::find(vDictionary.begin(), vDictionary.end(), tempNGram) != vDictionary.end()))
				vDictionary.push_back(tempNGram);

			mvSegmentNgrams.push_back(tempNGram);
			jBlockOffset++;

		}
		CLogger::GetLogger()->Log("Block were Splited into Ngrams - createAnagramMatrix() Finished Succesfully");
		/*TODO:write to File and save*/
		mfSegmentNgramsfilePath = NgramsFilesPath;
		mfSegmentNgramsfilePath.append("NgramFromSeg" + std::to_string(miSegmentNumber));
		//mfSegmentNgramsfile.open(mfSegmentNgramsfilePath);

		SaveNgramDataToFile();
		/****************************/
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

vector<string>& CSegment::ReadNgramDataFromFile(void)
{
	string temp;
	vector<string> Ngrams;
	ifstream SegmentNgramsfile;
	SegmentNgramsfile.open(mfSegmentNgramsfilePath);
	if (!SegmentNgramsfile.is_open())
		throw CError("can't open SegmentNgramsfile");

	while (!SegmentNgramsfile.eof())
	{
	 //temp << mfSegmentCFMfile;
		getline(SegmentNgramsfile, temp);
		Ngrams.push_back(temp);
	}
	SegmentNgramsfile.close();
	return Ngrams;
}

void CSegment::SaveNgramDataToFile()
{
	for each (string Ngram in mvSegmentNgrams)
	{
		/*open File for writing and generate filename*/
		ofstream fSegmentNgramsfile;
		fSegmentNgramsfile.open(mfSegmentNgramsfilePath);
		fSegmentNgramsfile << Ngram << endl;
		fSegmentNgramsfile.close();
	}
}

CSegment & CSegment::getCSegment(void)
{
	// TODO: insert return statement here
	return *this;
}

CSegment::~CSegment()
{
	// לא לשכוח שחרורים של כל המטריצות

	CError Err(""); Err.AddID("CText", __FUNCTION__);
	CLogger::GetLogger()->Log(Err.GetErrMsg());
	cout << "dss";

}

// 1) build CFM Matrix using vDictionary , save it in mfSegmentCFMfile
// 2) build SP Matrix using mfSegmentCFMfile, save it in mfSegmentSPfile: 
//    use the private function BuildSegmentSP(ofstream & mfSegmentCFMfile)
void CSegment::BuildSegmentCFMandSP(vector<string>& vDictionary)
{
	// use mfSegmentNgramsfile , finnaly save CFM mat to mfSegmentCFMfile
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		arma::mat segCFM(vDictionary.size(), mvSegmentNgrams.size());
		segCFM.fill(0);
		for (int i = 0; i < mvSegmentNgrams.size(); i++)
		{
			//size_t pos = NgramSeg[i] - dictionary->begin();
			auto  pos = find(vDictionary.begin(), vDictionary.end(), mvSegmentNgrams[i]) - vDictionary.begin();
			if (pos >= (int)vDictionary.size())
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
		string filename = "/CFM's/segCFM" + std::to_string(miSegmentNumber) + ".txt";
		segCFM.save(filename, arma::arma_ascii);
		mfSegmentCFMfileName = filename;
		//segCFM.load(filename);
		//arma::mat G;
		//G.load(filename);

		// time to build SP's
		// use Algorithm Class , finnaly save SP mat to mfSegmentSPfile
		//string message = "CFM created successfuly for seg " + std::to_string(miSegmentNumber) + "--> Starting build SP";
		//CLogger::GetLogger()->Log(message);
		CLogger::GetLogger()->Log("CFM created successfuly for seg " + std::to_string(miSegmentNumber) + "--> Starting build SP");
		mfSegmentSPfileName = CAlgorithms::BuildSPfile(segCFM);
		CLogger::GetLogger()->Log("SP created successfuly for seg " + std::to_string(miSegmentNumber) );
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

string& CSegment::GetSegmentSPfileName(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		return mfSegmentSPfileName;
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

#endif 
