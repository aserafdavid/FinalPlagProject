#include "CAlgorithms.h"

/*The QR Algorithms
input: NxN Matrix
output: NxN after QR decomposition
*/
void CAlgorithms::RunQrAlg(arma::mat &matrixA, arma::mat &matrixR)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		// QR-decomposition of matrix A, A is replaced with Q
		for (size_t i = 0; i < matrixA.n_cols; i++)
		{
			double r = dot(matrixA.col(i), matrixA.col(i));
			matrixR(i, i) = sqrt(r);
			matrixA.col(i) /= sqrt(r); //normalization
			for (size_t j = i + 1; j < matrixA.n_cols; j++)
			{
				double s = dot(matrixA.col(i), matrixA.col(j));
				matrixA.col(j) -= s*matrixA.col(i); //orthogonalization
				matrixR(i, j) = s;
			}
		}
	}
	catch (CError& Err) {
		Err.AddID("CAlgorithms", __FUNCTION__);
		throw Err;
	}
}

ofstream* CAlgorithms::BuildSPfile(ofstream & fSegmentCFMfile)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		// implementation here

		return &fSegmentCFMfile; // just for returning something for meanwhile
	}
	catch (CError& Err) {
		Err.AddID("CAlgorithms", __FUNCTION__);
		throw Err;
	}
}

// Tm = Transition Matrix between SP_i to SP_i+1
string & CAlgorithms::BuildTmBetweenSPs(CDynamicSystemSegment & Left, CDynamicSystemSegment & Right)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		string PathToMat;
		// implementation here

		return PathToMat;
	}
	catch (CError& Err) {
		Err.AddID("CAlgorithms", __FUNCTION__);
		throw Err;
	}
}


