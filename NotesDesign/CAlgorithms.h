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

	static void FindBestClusterization(const arma::mat & EVM, pair<int, map<int, int> >& BestClustersMap);
	static void BuildClustersVector(const arma::mat & EVM, const arma::mat & Centroids, map<int, int>& ClustersVector);
	static double CalcDistanceBetweenVectors(const arma::vec & vec1, const arma::vec & vec2);
	static double CalcSilhouetteCoefficient(const arma::mat & EVM, map<int, int>& ClustersVector, int ClustersNumber);
	static void CalcDistancesPerSegment(const arma::mat & EVM, map<int, int>& SegToClusterVector, int SegNum, double* avg_distance_in_cluster, double* avg_distance_out_cluster);

protected:

private:

};
#endif


