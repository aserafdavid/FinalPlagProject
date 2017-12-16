#ifndef Segment_H
#define Segment_H

/* includes */
#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
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
	CSegment(  string& SegmentData, int NgramSize, vector<string>& vDictionary);
	~CSegment();
	
	void BuildSegmentCFM(vector<string>& vDictionary);
	vector<string>& CSegment::ReadNgramDataFromFile();
	ofstream* GetSegmentSPfile(void);
	size_t miSegSize;

protected:
	virtual  bool SaveNgramDataToFile();
	CSegment& getCSegment(void);

	//virtual  bool LoadData(void);
	ifstream mfSegmentCFMfile; // instead mat
	ofstream* mfSegmentSPfile; // instead mat
	vector<string> mvSegmentNgrams;
	int miNgramSize;
	int miSegmentSize;
	vector<string> mvDictionary;

	
private:

	string msSegmentData;
	string mfSegmentNgramsfilePath;
	ofstream mfSegmentNgramsfile; // instead vector
	
	void BuildSegmentSP(ofstream& mfSegmentCFMfile);
};
#endif

