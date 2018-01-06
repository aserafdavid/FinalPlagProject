#pragma once
#ifndef _Text_h_
#define _Text_h_

/* includes */
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include "CDynamicSystemSegment.h"
#include "CClusteredSegment.h"

//#include "CSegment.h"
//#include "Logger.h"
//#include "CError.h"

using namespace std;

#define DeafultSegmentSize 40
#define DeafultNgramSize 3

/* class definition */
class CText
{
public:
	CText(string InputFileName, string stopWordFilePATH, string TempFilesPath, AprroachModel Aprroach, int SegmentSize = DeafultSegmentSize, int NgramSize = DeafultNgramSize);
	~CText();
	map<int, double> GetSegmentsApproximationErrorMap(void);
	string mPathToTempFiles;

protected:
	string msTmeasMatricesfileName; // instead mat

private:
	string mfInputFile;
	string mfStopWordFile;
	string mfInputFileWithoutstopWord;
	AprroachModel meAprroach;

	int miSegmentSize;
	int miNgramSize;
	vector<shared_ptr<CDynamicSystemSegment>> mvDsSegments;
	vector<shared_ptr<CClusteredSegment>> mvClSegments;
	vector<string> mvDictionary;
	vector<string> mvStopWordList;

	void readStopWordFile(void);
	void RemoveStopWordList(void);
	void DivideTextIntoSegments(void);

	/* DS */
	//Tmeas - transition measure between all the TM of segments
	string  msTmeasFileName; // instead mat
	void CompleteDsProcess(void);
	void CompleteClProcess(void);

	void BuildTmeas(void);
	map<int, double> mmSegmentsApproximationError;
	void SetApproximationErrorBetweenSegments(void);

	/* CL */
	arma::mat mEVM;

};
#endif
