#include "CAlgorithms.h"


#include <R.h>

//using namespace Rcpp;

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

// class definition
class SortData {
public:
	uword index;
	double value;

	// constructors
	SortData();
	SortData(uword&, const double&);
	//	// overloaded < (is less) operator for sorting and ordering
	//	bool operator< (const SortData&);
	//	// overloaded > (is greater) operator for sorting and ordering
	//	bool operator> (const SortData&);
};

// constructors
inline SortData::SortData() {}
inline SortData::SortData(uword& first, const double& second) {
	index = first;
	value = second;
}

// compare two objects with < (is less) operator for sorting and ordering
bool sortDataIsLess(const SortData& left, const SortData& right) {
	return left.value < right.value;
}

// compare two objects with > (is greater) operator for sorting and ordering
bool sortDataIsGreater(const SortData& left, const SortData& right) {
	return left.value > right.value;
}

// compute order of observations
// stable sorting is not necessary since ties are broken by averaging
uvec order(const vec& x, const bool& decreasing) {
	// initialize data structure for sorting
	const uword n = x.n_elem;
	vector<SortData> foo(n);
	for (uword i = 0; i < n; i++) {
		foo[i] = SortData(i, x(i));
	}
	// call STL's sort()
	if (decreasing) {
		sort(foo.begin(), foo.end(), sortDataIsGreater);
	}
	else {
		sort(foo.begin(), foo.end(), sortDataIsLess);
	}
	// construct and return vector of indices
	uvec indices(n);
	for (uword i = 0; i < n; i++) {
		SortData bar = foo[i];
		indices(i) = bar.index;
	}
	return indices;
}

// compute increasing order of observations
uvec order(const vec& x) {
	return order(x, false);
}

// compute ranks of observations in a vector
// function name 'rank' causes error with clang++ on OS X Mavericks
vec rank_ccaPP(const vec& x) {
	const uword n = x.n_elem;
	uword i, j, k;
	// compute order of observations
	uvec ord = order(x);
	// compute ranks (break ties by taking average)
	vec ranks(n);
	for (i = 0; i < n; i = j + 1) {
		j = i;
		// check if there is a series of equal values
		while ((j < n - 1) && (x(ord(j)) == x(ord(j + 1)))) {
			j++;
		}
		// break ties by average rank, otherwise this gives just the rank
		for (k = i; k <= j; k++) {
			ranks(ord(k)) = (i + j + 2) / 2.0;
		}
	}
	// return ranks
	return ranks;
}

double corPearson(const arma::vec& x, const arma::vec& y) {
	mat corXY = cor(x, y);	// arma function cor() always returns matrix
	return corXY(0, 0);
}

double CAlgorithms::corSpearman(const arma::vec& x, const arma::vec& y) {
	const uword n = x.n_elem;
	// make sure it returns NA in the presence of NA's
	for (uword i = 0; i < n; i++) 
	{
		//if (ISNAN(x(i)) || ISNAN(y(i))) return(NA_REAL);
		if (isnan(x(i)) || isnan(y(i))) return 0;
	}
	// compute ranks
	vec ranksX = rank_ccaPP(x), ranksY = rank_ccaPP(y);
	// return Pearson correlation for ranks
	return corPearson(ranksX, ranksY);
}

double CAlgorithms::corSpearman_adir(const arma::vec& x, const arma::vec& y) 
{
	return 0;
}


string& CAlgorithms::BuildSPfile(arma::mat& mSegmentCFmMat, string savePath, int segNum)
{
	try {
		CError Err(""); Err.AddID("CAlgorithms", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		// implementation here
		arma::mat segSP(mSegmentCFmMat.n_cols, mSegmentCFmMat.n_cols);
		segSP.fill(0);
		for(int i=0; i< mSegmentCFmMat.n_cols ; ++i)
			for (int j = i; j < mSegmentCFmMat.n_cols; ++j)
			{
				if (i == j)
				{
					segSP(i, j) = 1;
				}
				else
				{
					double res = corSpearman(mSegmentCFmMat.col(i), mSegmentCFmMat.col(j));
					segSP(i, j) = res;
					segSP(j, i) = res;
				}
			}

		string fileName = savePath;
		fileName.append("\\SP's\\segSP" + std::to_string(segNum));
		segSP.save(fileName, arma::arma_ascii);
		return fileName;
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


