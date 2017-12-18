
#include "CSegment.h"

#ifndef _Algorithms_h_
#include "CAlgorithms.h"

/*in this default c'tor should create the file and update the Dictionary*/
CSegment::CSegment(CSegment & origin)
{

}

vector<string>& CSegment::ReadNgramDataFromFile(void)
{
	string temp;
	vector<string> Ngrams;
	ifstream SegmentNgramsfile;
	SegmentNgramsfile.open(mfSegmentNgramsfilepath);
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

	if (!mfSegmentNgramsfile.is_open())
		mfSegmentNgramsfile.open(mfSegmentNgramsfilepath);
	for each (string Ngram in mvSegmentNgrams)
	{
		/*open File for writing and generate filename*/
		mfSegmentNgramsfile << Ngram << endl;
	}
	mfSegmentNgramsfile.close();
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
		
		
		string filename = mfSegmentNgramsfilepath;
		filename.append("\\CFM's\\segCFM" + std::to_string(miSegmentNumber));
		segCFM.save(filename, arma::arma_ascii);
		mfSegmentCFMfileName = filename;
		//segCFM.load(filename);
		//arma::mat G;
		//G.load(filename);

		// time to build SP's
		// use Algorithm Class , finnaly save SP mat to mfSegmentSPfile
		CLogger::GetLogger()->Log("CFM created successfuly for seg " + std::to_string(miSegmentNumber) + "--> Starting build SP");
		mfSegmentSPfileName = CAlgorithms::BuildSPfile(segCFM, mfSegmentNgramsfilepath, miSegmentNumber);
		CLogger::GetLogger()->Log("SP created successfuly for seg " + std::to_string(miSegmentNumber) );
	}
	catch (CError& Err) {
		Err.AddID("CSegment", __FUNCTION__);
		throw Err;
	}
}


string CSegment::GetSegmentSPfileName(void)
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
