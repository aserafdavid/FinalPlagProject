#include <iostream>
#include <armadillo>
#include "CText.h"

using namespace std;
using namespace arma;

int main(int argc, const char **argv) {


	string path = argv[0];
	string ext = "x64\\Debug\\PlagiarismDetection.exe";
	if (path != ext &&
		path.size() > ext.size() &&
		path.substr(path.size() - ext.size()) == ext)
				path = path.substr(0, path.size() - ext.size());

	if (Setinfrastructure(path))
	{
		path.append("tempFiles");
		Global_PathToTempFiles = path;
		CText ct("Bildschirmtext.txt", "StopWords.txt", path);
	}
	//fileManager fm("Bildschirmtext.txt", "StopWords.txt");
	//fm.readFile(40);
	//fm.createAnagramMatrix(4);
	//fm.CreateAllCFMsMatrixes();

	//// Initialize the random generator
	//arma::arma_rng::set_seed_random();

	//// Create a 4x4 random matrix and print it on the screen
	//arma::Mat<double> A = arma::randu(4, 4);
	//std::cout << "A:\n" << A << "\n";

	//// Multiply A with his transpose:
	//std::cout << "A * A.t() =\n";
	//std::cout << A * A.t() << "\n";

	//// Access/Modify rows and columns from the array:
	//A.row(0) = A.row(1) + A.row(3);
	//A.col(3).zeros();
	//std::cout << "add rows 1 and 3, store result in row 0, also fill 4th column with zeros:\n";
	//std::cout << "A:\n" << A << "\n";

	//// Create a new diagonal matrix using the main diagonal of A:
	//arma::Mat<double>B = arma::diagmat(A);
	//std::cout << "B:\n" << B << "\n";

	//// Save matrices A and B:
	//A.save("A_mat.txt", arma::arma_ascii);
	//B.save("B_mat.txt", arma::arma_ascii);


	return 0;

}