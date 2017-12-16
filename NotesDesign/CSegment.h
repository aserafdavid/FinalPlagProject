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


using namespace std;

/* class definition */
class CSegment
{
public:
	CSegment( CSegment& origin);
	CSegment(  string& SegmentData, int NgramSize, vector<string>& vDictionary);
	~CSegment();
	
	void BuildSegmentCFMandSP(vector<string>& vDictionary);
	vector<string>& CSegment::ReadNgramDataFromFile();
	string& GetSegmentSPfileName(void);
	int miSegSize;

protected:
	virtual  void SaveNgramDataToFile();
	
	//virtual  bool LoadData(void);
	string mfSegmentCFMfileName; // instead mat - consider to delete it if not nececarry 
	string mfSegmentSPfileName; // instead mat
	vector<string> mvSegmentNgrams;
	int miNgramSize;
	int miSegmentSize;
	int miSegmentNumber;
	vector<string> mvDictionary;

private:
	string msSegmentData;
	string mfSegmentNgramsfilePath;
	//ofstream mfSegmentNgramsfile; // instead vector
	
};
#endif

