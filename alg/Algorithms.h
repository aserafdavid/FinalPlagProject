#pragma once
#include <iostream>
#include <armadillo>

class Algorithms
{
public:
	Algorithms();
	//void RunQrAlg(arma::mat &A,arma::mat &R);
	~Algorithms();
	void Algorithms::RunQrAlg(arma::mat & matrixA, arma::mat & matrixR);
};


