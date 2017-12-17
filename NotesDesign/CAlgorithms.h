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
	static double CAlgorithms::corSpearman(const arma::vec& x, const arma::vec& y);
	static string BuildSPfile(arma::mat& mSegmentCFmMat, string savePath, int segNum);
	static string BuildTmBetweenSPs(CDynamicSystemSegment& Left, CDynamicSystemSegment& Right);

	double CAlgorithms::corSpearman_adir(const arma::vec& x, const arma::vec& y);

protected:

private:

};
#endif


