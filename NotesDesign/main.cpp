#include <iostream>
#include <armadillo>
#include "CText.h"
//#include "CAlgorithms.h"
#include "Cpipe.h"
#include <thread> 

using namespace std;
using namespace arma;



Pipe p;
enum pipe_in  {  /*messagez from the UI*/
			    EXAMINEPATHFILE/**/
				,EXAMINESTOPWORDFILE
				, NGRAMSIZE
				,SEGMENTSIZE
				,STARTWORK
};


volatile static bool startWork = false;
static std::map<std::string, pipe_in> s_mapPipeValues;

//string hashPipeIn(string const& inString)
//{
//	s_mapPipeValues["STARTWORK"] = STARTWORK;
//	s_mapPipeValues["EXAMINEPATHFILE"] = EXAMINEPATHFILE;
//	s_mapPipeValues["EXAMINESTOPWORDFILE"] = EXAMINESTOPWORDFILE;
//	s_mapPipeValues["NGRAMSIZE"] = NGRAMSIZE;
//	s_mapPipeValues["SEGMENTSIZE"] = SEGMENTSIZE;
//}




void BackgroundConnectionManager(void)
{
	bool isConnect = p.connect();

	string ans;
	while (!isConnect)
	{
		cout << "trying connect again.." << endl; /* move to Logger*/
		Sleep(5000);
		isConnect = p.connect();
	}

	char msgToGraphics[1024];
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics

		// YOUR CODE
		strcpy_s(msgToGraphics, "YOUR CODE"); // msgToGraphics should contain the result of the operation
											  // return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);

		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();

		switch (s_mapPipeValues[msgFromGraphics])
		{
		case STARTWORK:
			/*Set vars and run algorithms */
			break;
		case EXAMINEPATHFILE:
		break;
		case EXAMINESTOPWORDFILE:
		break;
		case NGRAMSIZE:
		break;
		case SEGMENTSIZE:
		break;
	

		}

	}

	p.close();
}



int main(int argc, const char **argv) {


	
	/*while (!p.connect());
	p.sendMessageToGraphics("HandshakCPPStart");
	p.getMessageFromGraphics();
	std:thread(BackgroundConnectionManager);*/

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

	/*std::this_thread::sleep_for(std::chrono::milliseconds(10000)); 
	p.sendMessageToGraphics("HandshakCPPStart");*/

	string path = argv[0];
	string ext = "x64\\Debug\\PlagiarismDetection.exe";
	if (path != ext &&
		path.size() > ext.size() &&
		path.substr(path.size() - ext.size()) == ext)
				path = path.substr(0, path.size() - ext.size());

	if (Setinfrastructure(&path))
	{
		while (!startWork)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		}
		Global_PathToTempFiles = path;
		//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, DS_Aprroach);
		//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, CL_Aprroach);
		CText ct("Bildschirmtext1.txt", "StopWords.txt", path, Both_Aprroaches);


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