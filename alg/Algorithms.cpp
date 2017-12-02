#include "Algorithms.h"

using namespace arma;

Algorithms::Algorithms()
{
}


Algorithms::~Algorithms()
{
}

/*The QR Algorithms 
input: NxN Matrix 
output: NxN after QR decomposition 
*/
void Algorithms::RunQrAlg(arma::mat &matrixA,arma::mat &matrixR)
{
	// QR-decomposition of matrix A, A is replaced with Q
	{
		for (size_t i = 0; i < matrixA.n_cols; i++) {
			double r = dot(matrixA.col(i), matrixA.col(i));
			matrixR(i, i) = sqrt(r);
			matrixA.col(i) /= sqrt(r); //normalization
			for (size_t j = i + 1; j < matrixA.n_cols; j++) {
				double s = dot(matrixA.col(i), matrixA.col(j));
				matrixA.col(j) -= s*matrixA.col(i); //orthogonalization
				matrixR(i, j) = s;
			}
		}
	}
}