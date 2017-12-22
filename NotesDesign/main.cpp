#include <iostream>
#include <armadillo>
#include "CText.h"
//#include "CAlgorithms.h"

using namespace std;
using namespace arma;

int main(int argc, const char **argv) {

	//vec x, y;
	//x << 86 << 112 << 106 << 113 << 110 << 97 << 100 << 99 << 103 << 101;
	//y << 0 << 6 << 7 << 12 << 17 << 20 << 27 << 28 << 29 << 50 ;
	//x << 50 << 175 << 270 << 375 << 425 << 580 << 710 << 790 << 890 << 980;
	//y << 1.80 << 1.20 << 2 << 1 << 1 << 1.20 << 0.8 << 0.6 << 1 << 0.85;
	//x << 100 << 102 << 102;
	//y << 257 << 264 << 257;
	//double res;
	//res = CAlgorithms::corSpearman(x,y);
	//cout << "result: " << res; 

	string path = argv[0];
	string ext = "x64\\Debug\\PlagiarismDetection.exe";
	if (path != ext &&
		path.size() > ext.size() &&
		path.substr(path.size() - ext.size()) == ext)
				path = path.substr(0, path.size() - ext.size());

	if (Setinfrastructure(&path))
	{
		Global_PathToTempFiles = path;
		CText ct("Bildschirmtext1.txt", "StopWords.txt", path);

		cout << "Aproximation Errors by Segments:\n";
		map<int, double> ApproximationErrorMap = ct.GetSegmentsApproximationErrorMap();
		for (std::map<int, double>::iterator it = ApproximationErrorMap.begin(); it != ApproximationErrorMap.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
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

	cout << "\n\nThe End! \n\n ";
	getchar();
	return 0;

}