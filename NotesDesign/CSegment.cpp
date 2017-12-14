
#include "CSegment.h"


/*in this default c'tor should create the file and update the Dictionary*/
CSegment::CSegment(CSegment & origin)
{
	miNgramSize = origin.miNgramSize;
	msSegmentData = origin.msSegmentData;
	
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
		mfSegmentNgramsfilePath.append("NgramFromSeg" + std::to_string(GetSegId()));
		mfSegmentNgramsfile.open(mfSegmentNgramsfilePath);

		SaveNgramDataToFile();
		/****************************/
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

vector<string> CSegment::ReadNgramDataFromFile(void)
{
	string temp;
	vector<string> Ngrams;
	if (!mfSegmentCFMfile.is_open())
		mfSegmentCFMfile.open(mfSegmentNgramsfilePath);

	while (!mfSegmentCFMfile.eof())
	{
	 //temp << mfSegmentCFMfile;
		getline(mfSegmentCFMfile, temp);
		Ngrams.push_back(temp);
	}
	return Ngrams;

}

bool CSegment::SaveNgramDataToFile()
{
	if (!mfSegmentNgramsfile.is_open())
		return false;

	/*open File for writing and generate filename*/

	for each (string Ngram in mvSegmentNgrams)
		mfSegmentNgramsfile << Ngram << endl;
	return true;
}

CSegment::~CSegment() noexcept(false)
{
	// לא לשכוח שחרורים של כל המטריצות
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

// 1) build CFM Matrix using vDictionary , save it in mfSegmentCFMfile
// 2) build SP Matrix using mfSegmentCFMfile, save it in mfSegmentSPfile: 
//    use the private function BuildSegmentSP(ofstream & mfSegmentCFMfile)
void CSegment::BuildSegmentCFM(vector<string>& vDictionary)
{
	// use mfSegmentNgramsfile , finnaly save CFM mat to mfSegmentCFMfile
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());
	
	
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}

ofstream * CSegment::GetSegmentSPfile(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		return mfSegmentSPfile;
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}
#ifndef _Algorithms_h_
#include "CAlgorithms.h"
#endif 


void CSegment::BuildSegmentSP(ofstream & mfSegmentCFMfile)
{
	// use Algorithm Class , finnaly save SP mat to mfSegmentSPfile
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		mfSegmentSPfile = CAlgorithms::BuildSPfile(mfSegmentCFMfile);

	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}
