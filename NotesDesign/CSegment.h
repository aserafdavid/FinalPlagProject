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
	CSegment(const CSegment& origin);
	//1) Create Ngrams From Segment according to NgramSize , update vDictionary accordingly.
	//2) finnaly Save vSegmentNgrams to mfSegmentNgramsfile 
	CSegment(string& SegmentData, int NgramSize, string pathTempFiles, vector<string>& vDictionary);
	~CSegment();
	
	void BuildSegmentCFMandSP(vector<string>& vDictionary);
	vector<string>& CSegment::ReadNgramDataFromFile();
	size_t miSegSize;

	string GetSegmentSPfileName(void);
	string GetSegmentData(void);

protected:
	virtual  void SaveNgramDataToFile();
	CSegment& getCSegment(void);
	string mfSegmentCFMfileName; // instead mat - consider to delete it if not nececarry 
	string mfSegmentSPfileName; // instead mat
	string mfSegmentNgramsfilepath;
	vector<string> mvSegmentNgrams;
	int miNgramSize;
	int miSegmentSize;
	int miSegmentNumber;
	vector<string> mvDictionary;

	
private:

	string msSegmentData;
	ofstream mfSegmentNgramsfile; // instead vector
	
};
#endif

