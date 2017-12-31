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



Pipe p(0);
std::mutex mtx;

static bool AbortRunner = false;
volatile bool* abortRun =&AbortRunner;
string fileNamePath, StopwordsNamePath;
int segSize, NgramSize;

enum pipe_in {  /*messagez from the UI*/
	EXAMINEPATHFILE/**/
	, EXAMINESTOPWORDFILE
	, NGRAMSIZE
	, SEGMENTSIZE
	, STARTWORK
	, QUIT
	, CANCELRUN
};





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
void BackgroundEngine(string argv)
{

	SetThreadPriority(GetCurrentThread(), HIGH_PRIORITY_CLASS);//set high priority to the thread

	printf("threadstart\n");
	while (true)
	{
		printf("alive");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

		if (*abortRun == true)/*Should be implanted in algorithm code*/
		{
			printf("Worker aborted");
			HANDLE t = GetCurrentThread();
			TerminateThread(t, 0);

		}
	};

	string path = argv;
	string ext = "x64\\Debug\\PlagiarismDetection.exe";
	if (path != ext &&
		path.size() > ext.size() &&
		path.substr(path.size() - ext.size()) == ext)
		path = path.substr(0, path.size() - ext.size());

	if (Setinfrastructure(&path))
	{

		//	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		//}
		Global_PathToTempFiles = path;
		//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, DS_Aprroach);
		//CText ct("Bildschirmtext1.txt", "StopWords.txt", path, CL_Aprroach);
		//mtx.lock();
		//if (abortRun == true)
		//{
		//	TerminateThread(std::this_thread::get_id, 0);
		//}
		//mtx.unlock();
		CText ct(fileNamePath, StopwordsNamePath, path, Both_Aprroaches, SEGMENTSIZE, NGRAMSIZE);


		cout << "Aproximation Errors by Segments:\n";
		map<int, double> ApproximationErrorMap = ct.GetSegmentsApproximationErrorMap();
		for (std::map<int, double>::iterator it = ApproximationErrorMap.begin(); it != ApproximationErrorMap.end(); ++it)
			cout << it->first << " => " << it->second << '\n';
	}


	cout << "\n\nThe End! \n\n ";
	getchar();
}

static int counter=0;
std::vector<std::thread*> threads;
int main(int argc, const char **argv) {

	bool CloseApp = false;
	bool isOnLoadingStage = false;
	//HANDLE workthread;
	thread w;
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
	//std::thread work(BackgroundConnectionManager, argv[0]);
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
				*abortRun = false;
				isOnLoadingStage = true;
				LOGGER->GetLogger()->Log("STARTWORK Message from app");
				p.close();

				/*Create loading pipe and Run algorithms*/
				bool isConnect = p.connect();
				while (!isConnect)
				{
					cout << "trying connect again.." << endl; /* move to Logger*/
					Sleep(5000);
					isConnect = p.connect();
				}

				thread *t =new std::thread(BackgroundEngine, argv[0]);
				
				while (isOnLoadingStage)
				{
					//FlushFileBuffers(p.hPipe);
					msgFromGraphics = p.getMessageFromGraphics();
					if (msgFromGraphics != "")
					{
						switch (s_mapInPipeValues[msgFromGraphics])
						{
						case CANCELRUN:

							//TerminateThread((*t).native_handle(), 1);
							//CloseHandle(tradesRun[counter++]);
							//CloseHandle(w.native_handle());
							*abortRun = true;
							LOGGER->GetLogger()->Log("CANCELRUN Message from app");
							p.sendMessageToGraphics("ACCEPTED");
							isOnLoadingStage = false;
							p.close();
							isConnect = p.connect();
							while (!isConnect)
							{
								cout << "trying connect again.." << endl; /* move to Logger*/
								Sleep(5000);
								isConnect = p.connect();
							}
							break;

						case QUIT:
							//TODO change volatile to stop work
							//TerminateThread(tradesRun[counter], 0);
							//CloseHandle(tradesRun[counter]);
							//TerminateThread(w.native_handle(), 0);
							//CloseHandle(w.native_handle());
							mtx.lock();
							*abortRun = true;
							mtx.unlock();
							LOGGER->GetLogger()->Log("QUIT Message from app");
							p.sendMessageToGraphics("ACCEPTED");
							exit(1);
							break;

						default:
							
							break;
						}
						//w.~thread();
						//TerminateThread(w.native_handle(), 0);
						
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
			}
				break;

			case EXAMINEPATHFILE:
				fileNamePath = p.getMessageFromGraphics();
				LOGGER->GetLogger()->Log("EXAMINEPATHFILE Message from app");
				break;

			case EXAMINESTOPWORDFILE:
				StopwordsNamePath = p.getMessageFromGraphics();
				LOGGER->GetLogger()->Log("EXAMINESTOPWORDFILE Message from app");
				break;

			case NGRAMSIZE:
				NgramSize = stoi(p.getMessageFromGraphics().c_str());
				LOGGER->GetLogger()->Log("NGRAMSIZE Message from app");
				break;

			case SEGMENTSIZE:
				segSize = stoi(p.getMessageFromGraphics().c_str());
				LOGGER->GetLogger()->Log("SEGMENTSIZE Message from app");
				break;

			case CANCELRUN:
				//w.~thread();
				//TerminateThread(w.native_handle(), 0);
				//CloseHandle(w.native_handle());
				LOGGER->GetLogger()->Log("CANCELRUN Message from app");
				p.sendMessageToGraphics("ACCEPTED");
				break;

			case QUIT:
				//TerminateThread(w.native_handle(), 0);
				//CloseHandle(w.native_handle());
				LOGGER->GetLogger()->Log("QUIT Message from app");
				exit(1);
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