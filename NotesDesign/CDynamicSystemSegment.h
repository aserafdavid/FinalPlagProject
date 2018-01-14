#ifndef SegmentDynamicSystem_H
#define SegmentDynamicSystem_H

/* includes */
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include "Logger.h"
//#include "CError.h"
//#include "CAlgorithms.h"

//using namespace std;
#include "CSegment.h"

/* class definition */
class CDynamicSystemSegment : public CSegment
{
public:
	CDynamicSystemSegment& GetCDynamicSystemSegment(void);
	CDynamicSystemSegment(const CDynamicSystemSegment& origin);
	CDynamicSystemSegment(string SegmentData, int NgramSize, string pathTempFiles, vector<string>& vDictionary);
	~CDynamicSystemSegment();

	/*
	* Return mat X such as Ax=B
	* Input: some other mat.save file path as mat B
	* Using: current Csegment sp mat.save
	*/
	void CalcTransitionMatrix(string FileToSPMat);
	string GetSegmentTmFileName(void);
	void SetSegmentTmFileName(string& FileName);
	double GetApproximationError(void);
	void SetApproximationError(double ApproximationError);
protected:

private:
	// TM = Transition Matrix between SP_i to SP_i+1
	string  msSegmentTmFileName; // instead mat
	string msSegmentData;
	double	mfApproximationError;
	void DivideIntoNgrams();


};
#endif

