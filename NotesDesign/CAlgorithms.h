#ifndef _Algorithms_h_
#define _Algorithms_h_

/* includes */
#include "CDynamicSystemSegment.h"
#include <iostream>
#include <string.h>
#include <armadillo>
//#include "Logger.h"
//#include "CError.h"

//using namespace std;
using namespace arma;

/* class definition */
class CAlgorithms
{
public:
	CAlgorithms() {};
	~CAlgorithms() {};

	static void RunQrAlg(arma::mat & matrixA, arma::mat & matrixR);
	static string& BuildSPfile(arma::mat& mSegmentCFmMat);
	static string& BuildTmBetweenSPs(CDynamicSystemSegment& Left, CDynamicSystemSegment& Right);


protected:

private:

};
#endif


