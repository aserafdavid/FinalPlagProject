#pragma once
#ifndef _Text_h_
#define _Text_h_

/* includes */
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
//#include "CSegment.h"
#include "CDynamicSystemSegment.h"
//#include "Logger.h"
//#include "CError.h"

using namespace std;

#define DeafultSegmentSize 40
#define DeafultNgramSize 3

/* class definition */
class CText
{
public:
	CText(string InputFileName, string stopWordFilePATH, string TempFilesPath, int SegmentSize = DeafultSegmentSize, int NgramSize = DeafultNgramSize);
	~CText();
	map<int, double> GetSegmentsApproximationErrorMap(void);
	string mPathToTempFiles;

protected:
	string msTmeasMatricesfileName; // instead mat

private:
	string mfInputFile;
	string mfStopWordFile;
	string mfInputFileWithoutstopWord;

	int miSegmentSize;
	int miNgramSize;
	vector<shared_ptr<CDynamicSystemSegment>> mvSegments;
	vector<string> mvDictionary;
	vector<string> mvStopWordList;


	void readStopWordFile(void);
	void RemoveStopWordList(void);
	void DivideTextIntoSegments(void);

	/* DS */
	//Tmeas - transition measure between all the TM of segments
	string  msTmeasFileName; // instead mat
	void BuildTmeas(void);
	map<int, double> mmSegmentsApproximationError;
	void SetApproximationErrorBetweenSegments(void);

};
#endif
