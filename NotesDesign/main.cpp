#include <iostream>
#include <armadillo>
#include "CText.h"
//#include "CAlgorithms.h"
#include "Cpipe.h"
#include <thread> 
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace arma;



Pipe p;
std::mutex mtx;

enum pipe_in {  /*messagez from the UI*/
	EXAMINEPATHFILE/**/
	, EXAMINESTOPWORDFILE
	, NGRAMSIZE
	, SEGMENTSIZE
	, STARTWORK
	, QUIT
	,CANCELRUN
};





volatile static bool startWork = false;
static std::map<std::string, pipe_in> s_mapInPipeValues;

/*Thread arguments*/
std::condition_variable cv;
std::mutex m;

void InithashPipeIn()
{
	s_mapInPipeValues["STARTWORK"] = STARTWORK;
	s_mapInPipeValues["EXAMINEPATHFILE"] = EXAMINEPATHFILE;
	s_mapInPipeValues["EXAMINESTOPWORDFILE"] = EXAMINESTOPWORDFILE;
	s_mapInPipeValues["NGRAMSIZE"] = NGRAMSIZE;
	s_mapInPipeValues["SEGMENTSIZE"] = SEGMENTSIZE;
	s_mapInPipeValues["QUIT"] = QUIT;
	s_mapInPipeValues["CANCELRUN"] = CANCELRUN;
}


//TODO : add volatile var to tell background worker to stop work and 
void BackgroundConnectionManager(string argv,string FILENAMEPATH,string STOPWORDFILEPATH,int NGRAMSIZE,int SEGMENTSIZE)
{
	SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);//set high priority to the thread
	//std::unique_lock<std::mutex> lk(m);
	//cv.wait(lk, [] {return startWork; });
	//cv.notify_one();

	mtx.lock();/*Dont start run until getting signal from main*/
	while (true);

	string path = argv;
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
		CText ct(FILENAMEPATH, STOPWORDFILEPATH, path, Both_Aprroaches, SEGMENTSIZE, NGRAMSIZE);


		cout << "Aproximation Errors by Segments:\n";
		map<int, double> ApproximationErrorMap = ct.GetSegmentsApproximationErrorMap();
		for (std::map<int, double>::iterator it = ApproximationErrorMap.begin(); it != ApproximationErrorMap.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
	}


	cout << "\n\nThe End! \n\n ";
	getchar();
}


int main(int argc, const char **argv) {

	//bool isConnect = p.connect();
std:thread *workthread;
	string fileNamePath,StopwordsNamePath;
	int segSize, NgramSize;
	InithashPipeIn();
	int workID;
	bool isConnect = p.connect();


	while (!isConnect)
	{
		cout << "trying connect again.." << endl; /* move to Logger*/
		Sleep(5000);
		isConnect = p.connect();
	}

	char msgToGraphics[1024];
	string msgFromGraphics = "";
	char buffer[1024];
	bool t;
	while (true)
	{
		FlushFileBuffers(p.hPipe);
		msgFromGraphics = p.getMessageFromGraphics();
		if (msgFromGraphics != "")
		{
			switch (s_mapInPipeValues[msgFromGraphics])
			{
			case STARTWORK:
			{
				using namespace std;
				startWork = true;
				printf("STARTWORKDAVID");
				strcpy(buffer, "STARTWORK");/*Send App confirmation*/
				//FlushFileBuffers(p.hPipe);
				t = p.sendMessageToGraphics(buffer);
				LOGGER->GetLogger()->Log("STARTWORK Message from app");


				/*Run algorithms */
				segSize=stoi(p.getMessageFromGraphics().c_str());
				thread work(&BackgroundConnectionManager, argv[0], fileNamePath, StopwordsNamePath, NgramSize, segSize);
				workthread = &work;
				
			}
			case EXAMINEPATHFILE:
				fileNamePath=p.getMessageFromGraphics();
				LOGGER->GetLogger()->Log("EXAMINEPATHFILE Message from app");
				break;

			case EXAMINESTOPWORDFILE:
				StopwordsNamePath=p.getMessageFromGraphics();
				LOGGER->GetLogger()->Log("EXAMINESTOPWORDFILE Message from app");
				break;

			case NGRAMSIZE:
				NgramSize= stoi(p.getMessageFromGraphics().c_str());
				LOGGER->GetLogger()->Log("NGRAMSIZE Message from app");
				break;

			case SEGMENTSIZE:
				segSize=stoi(p.getMessageFromGraphics().c_str());
				LOGGER->GetLogger()->Log("SEGMENTSIZE Message from app");
				break;
			
			case CANCELRUN:
				workthread->~thread();
				LOGGER->GetLogger()->Log("CANCELRUN Message from app");
				p.sendMessageToGraphics("ACCEPTED");
				break;

			case QUIT:
				//TODO change volatile to stop work
				LOGGER->GetLogger()->Log("QUIT Message from app");
				break;

			default:
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				break;

			}

		}
	}

	//std:CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)BackgroundConnectionManager,0,0);
	//std::thread t(&BackgroundConnectionManager);

	//std::unique_lock<std::mutex> lk(m);
	//cv.wait(lk, [] {return startWork; });
	//cv.notify_one();


	/*std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	p.sendMessageToGraphics("HandshakCPPStart");*/

	//string path = argv[0];
	//string ext = "x64\\Debug\\PlagiarismDetection.exe";
	//if (path != ext &&
	//	path.size() > ext.size() &&
	//	path.substr(path.size() - ext.size()) == ext)
	//	path = path.substr(0, path.size() - ext.size());

	//if (Setinfrastructure(&path))
	//{
	//	while (!startWork)
	//	{
	//		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	//	}
	//	Global_PathToTempFiles = path;
	//	//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, DS_Aprroach);
	//	//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, CL_Aprroach);
	//	CText ct("Bildschirmtext1.txt", "StopWords.txt", path, Both_Aprroaches);


	//	cout << "Aproximation Errors by Segments:\n";
	//	map<int, double> ApproximationErrorMap = ct.GetSegmentsApproximationErrorMap();
	//	for (std::map<int, double>::iterator it = ApproximationErrorMap.begin(); it != ApproximationErrorMap.end(); ++it)
	//		cout << it->first << " => " << it->second << '\n';
	//}


	//cout << "\n\nThe End! \n\n ";
	//getchar();
	//return 0;

}