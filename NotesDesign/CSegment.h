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


using namespace std;

/* class definition */
class CSegment
{
public:
	CSegment( CSegment& origin);
	CSegment(  string& SegmentData, int NgramSize, vector<string>& vDictionary);
	~CSegment() noexcept(false);
	
	void BuildSegmentCFM(vector<string>& vDictionary);

	ofstream* GetSegmentSPfile(void);


protected:

	ofstream mfSegmentCFMfile; // instead mat
	ofstream* mfSegmentSPfile; // instead mat
	int miNgramSize;
	int miSegmentSize;
	const vector<string> mvDictionary;
private:
	string msSegmentData;
	ofstream mfSegmentNgramsfile; // instead vector
	void BuildSegmentSP(ofstream& mfSegmentCFMfile);
};
#endif

