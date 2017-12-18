#ifndef Segment_H
#define Segment_H

/* includes */
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "Logger.h"
#include "CError.h"
//#include "CAlgorithms.h"
#include <memory>

using namespace std;

/* class definition */
class CSegment 
{
public:
	CSegment( CSegment& origin);
	//1) Create Ngrams From Segment according to NgramSize , update vDictionary accordingly.
	//2) finnaly Save vSegmentNgrams to mfSegmentNgramsfile 
	CSegment(string& SegmentData, int NgramSize,string pathTempFiles, vector<string>& vDictionary)
		//: msSegmentData(SegmentData)
	{

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
			mfSegmentNgramsfilepath = pathTempFiles;
			//mPathToTempFiles.append("NgramFromSeg" + std::to_string(miSegmentNumber));
			pathTempFiles.append("\\SegNgrams\\NgramFromSeg" + std::to_string(miSegmentNumber));
			mfSegmentNgramsfile.open(pathTempFiles);

			SaveNgramDataToFile();
			/****************************/
		}
		catch (CError& Err) {
			Err.AddID("CSegment", __FUNCTION__);
			throw Err;
		}
	}
	~CSegment();
	
	void BuildSegmentCFMandSP(vector<string>& vDictionary);
	vector<string>& CSegment::ReadNgramDataFromFile();
	string GetSegmentSPfileName(void);
	size_t miSegSize;

protected:
	virtual  void SaveNgramDataToFile();
	CSegment& getCSegment(void);
	string mfSegmentCFMfileName; // instead mat - consider to delete it if not nececarry 
	string mfSegmentSPfileName; // instead mat
	vector<string> mvSegmentNgrams;
	int miNgramSize;
	int miSegmentSize;
	int miSegmentNumber;
	vector<string> mvDictionary;
	string mfSegmentNgramsfilepath;

	
private:

	string msSegmentData;
	ofstream mfSegmentNgramsfile; // instead vector
	
};
#endif

