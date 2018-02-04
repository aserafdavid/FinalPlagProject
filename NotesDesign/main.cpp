#include <iostream>
#include <armadillo>
#include "main.h"
#include "CText.h"
//#include "CAlgorithms.h"
#include <thread> 
#include <mutex>
#include <condition_variable>
#define _WIN32_WINNT 0x0500

#define DEBUG
#define RELEASE

using namespace std;
using namespace arma;

string ResultsVersionPath = "";

Pipe p(0), L(1), Pipe_UpdateUI(2);

static string path;


static bool AbortRunner = false;
volatile bool* abortRun = &AbortRunner;
string fileNamePath, StopwordsNamePath;
int segSize, NgramSize, PreferedClustersNumber;
AprroachModel ChosenAprroachModel;

static std::map<std::string, pipe_in> s_mapInPipeValues;
static std::map<std::string, pipe_out> s_mapOutPipeValues;

/*Thread arguments*/
std::condition_variable cv;
std::mutex m;

void InithashPipe()
{
	s_mapInPipeValues["STARTWORK"] = STARTWORK;
	s_mapInPipeValues["EXAMINEPATHFILE"] = EXAMINEPATHFILE;
	s_mapInPipeValues["EXAMINESTOPWORDFILE"] = EXAMINESTOPWORDFILE;
	s_mapInPipeValues["NGRAMSIZE"] = NGRAMSIZE;
	s_mapInPipeValues["SEGMENTSIZE"] = SEGMENTSIZE;
	s_mapInPipeValues["QUIT"] = QUIT;
	s_mapInPipeValues["CANCELRUN"] = CANCELRUN;
	s_mapInPipeValues["CHOSENRUN"] = CHOSENRUN;
	s_mapInPipeValues["PREFEREDCLUSTERSNUMBER"] = PREFEREDCLUSTERSNUMBER;

	s_mapOutPipeValues["Initialize"] = Initialize;
	s_mapOutPipeValues["OmitStopWordsStepFinished"] = OmitStopWordsStepFinished;
	s_mapOutPipeValues["BuldCFMsStepFinished"] = BuldCFMsStepFinished;
	s_mapOutPipeValues["BuildVocStepFinished"] = BuildVocStepFinished;
	s_mapOutPipeValues["ExtractNgramsStepFinished"] = ExtractNgramsStepFinished;
	s_mapOutPipeValues["ExamineResult"] = ExamineResult;
	s_mapOutPipeValues["DevideTextToSegStepFinished"] = DevideTextToSegStepFinished;
	s_mapOutPipeValues["CalcApproxMeasStepFinished"] = CalcApproxMeasStepFinished;
	s_mapOutPipeValues["CalcAQMeasureStepFinished"] = CalcAQMeasureStepFinished;
	s_mapOutPipeValues["BuildQsStepFinished"] = BuildQsStepFinished;
	s_mapOutPipeValues["BuildSPsStepFinished"] = BuildSPsStepFinished;
	s_mapOutPipeValues["FinishLoadingStage"] = FinishLoadingStage;

	s_mapOutPipeValues["EvmCreationFinished"] = EvmCreationFinished;
	s_mapOutPipeValues["ClusterizationFinished"] = ClusterizationFinished;
	s_mapOutPipeValues["ExamineCLResult"] = ExamineCLResult;

}
void TerminateIfNeeds(void)
{
	if (*abortRun == true)/*Should be implanted in algorithm code*/
	{
		printf("Worker aborted\n");
		HANDLE t = GetCurrentThread();
		TerminateThread(t, 0);
	}
}

void BackgroundEngine(string argv)
{
	
	path = argv;
	//path = "D:\\RunPlag\\PlagiarismDetection.exe";
	string ext = "PlagiarismDetection.exe";
	if (path != ext &&
		path.size() > ext.size() &&
		path.substr(path.size() - ext.size()) == ext)
		path = path.substr(0, path.size() - ext.size());

	
	if (Setinfrastructure(path))
	{
		ResultsVersionPath = path;
		Global_PathToTempFiles = path;
		//cout << Global_PathToTempFiles;
		CLogger::SetLogPath(path);
		CText ct(fileNamePath, StopwordsNamePath, path, ChosenAprroachModel, segSize, NgramSize, PreferedClustersNumber);
	}
	UpdateStates(FinishLoadingStage);

	cout << "\n\nThe End! \n\n ";
	getchar();
}

static int counter = 0;

void UpdateStates(pipe_out State)
{
	char *temp;

	if (*abortRun != true)
	{
		switch (State)
		{
		case OmitStopWordsStepFinished:
			//Pipe_UpdateUI.flush();
			Pipe_UpdateUI.sendMessageToGraphics("OmitStopWordsStepFinished");
			break;
		case DevideTextToSegStepFinished:
			//Pipe_UpdateUI.flush();
			Pipe_UpdateUI.sendMessageToGraphics("DevideTextToSegStepFinished");
			break;
		case ExtractNgramsStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("ExtractNgramsStepFinished");
			break;
		case BuildVocStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("BuildVocStepFinished");
			break;
		case BuldCFMsStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("BuldCFMsStepFinished");
			break;
		case BuildSPsStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("BuildSPsStepFinished");
			break;


		case BuildQsStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("BuildQsStepFinished");
			break;
		case CalcAQMeasureStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("CalcAQMeasureStepFinished");
			break;
		case CalcApproxMeasStepFinished:
			Pipe_UpdateUI.sendMessageToGraphics("CalcApproxMeasStepFinished");
			break;
		case ExamineResult:
			Pipe_UpdateUI.sendMessageToGraphics("ExamineResult");
			break;


		case EvmCreationFinished:
			Pipe_UpdateUI.sendMessageToGraphics("EvmCreationFinished");
			break;
		case ClusterizationFinished:
			Pipe_UpdateUI.sendMessageToGraphics("ClusterizationFinished");
			break;
		case ExamineCLResult:
			Pipe_UpdateUI.sendMessageToGraphics("ExamineCLResult");
			break;

		case FinishLoadingStage:
		{
			//ResultsVersionPath


			//temp = new char[ResultsVersionPath.size() + 1];
			//strcpy(temp, ResultsVersionPath.c_str());

			//DWORD nBufferLength = MAX_PATH;
			//char szCurrentDirectory[MAX_PATH + 1];
			//GetCurrentDirectory(nBufferLength, szCurrentDirectory);
			//szCurrentDirectory[MAX_PATH + 1] = '\0';

			temp = new char[path.size() + 1];
			strcpy(temp, path.c_str());

			//printf("-----------------david-------------\n");
			//cout << "path=" << path << endl;
			//cout << Global_PathForSending;
			//printf("temp = %s", temp);
			//printf("-----------------david-------------\n");
			Pipe_UpdateUI.sendMessageToGraphics("FinishLoadingStage");
			//cout << "Adir say: " << szCurrentDirectory << endl;
			Pipe_UpdateUI.sendMessageToGraphics(temp);
			Pipe_UpdateUI.getMessageFromGraphics();
		}break;

		case CancelRUN:
			Pipe_UpdateUI.sendMessageToGraphics("CancelRUN");
			break;

		default:
			break;
		}

	if (*abortRun == true)/*Should be implanted in algorithm code*/
	{

		printf("StatesUpdate  aborted\n");
		return;

	}
  }
}

int main(int argc, const char **argv) {

#ifdef DEBUG
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
#endif // DEBUG

	printf("%d %s", argc,argv[0]);
	static bool FirstTimePipeInit = false;
	bool CloseApp = false;
	bool isOnLoadingStage = false;
	InithashPipe();
	int workID;
	bool isConnect = p.connect();
	//Sleep(3000);//Avoid engine trying to connect bfore App loaded

	while (!isConnect)
	{
		cout << "trying connect again.." << endl; /* move to Logger*/
		Sleep(50);
		isConnect = p.connect();
	}

	char msgToGraphics[1024];
	string msgFromGraphics = "";
	char buffer[1024];

	while (true)
	{
		printf("Cstart Pipes");
		FlushFileBuffers(p.hPipe);
		msgFromGraphics = p.getMessageFromGraphics();

		if (msgFromGraphics != "")
		{
			printf("Cstart Pipes");
			switch (s_mapInPipeValues[msgFromGraphics])
			{
			case STARTWORK:
			{
				*abortRun = false;
				isOnLoadingStage = true;
				//LOGGER->GetLogger()->Log("STARTWORK Message from app");
				p.close();

				
					bool isConnect = L.connect();

					while (!isConnect)
					{
						cout << "trying connect again.." << endl; /* move to Logger*/
						Sleep(50);
						isConnect = L.connect();
					}

					isConnect = Pipe_UpdateUI.connect();

					while (!isConnect)
					{
						cout << "trying connect again.." << endl; /* move to Logger*/
						Sleep(50);
						isConnect = Pipe_UpdateUI.connect();
					}
				
				thread *t = new std::thread(BackgroundEngine, argv[0]);

				while (isOnLoadingStage)
				{
					FlushFileBuffers(L.hPipe);

					msgFromGraphics = L.getMessageFromGraphics();
					if (msgFromGraphics != "")
					{
						/*Handle In mesages*/
						switch (s_mapInPipeValues[msgFromGraphics])
						{
						case CANCELRUN:
						{
							*abortRun = true;
							UpdateStates(CancelRUN);
							//LOGGER->GetLogger()->Log("CANCELRUN Message from app");
							L.sendMessageToGraphics("ACCEPTED");
							isOnLoadingStage = false;
							L.close();
							//States.join();
							Pipe_UpdateUI.close();
							isConnect = p.connect();
							while (!isConnect)
							{
								cout << "trying connect again.." << endl; /* move to Logger*/
								Sleep(10);
								isConnect = p.connect();
							}
						}
							break;

						case QUIT:
							*abortRun = true;
							isOnLoadingStage = false;
							//LOGGER->GetLogger()->Log("QUIT Message from app");
							L.sendMessageToGraphics("ACCEPTED");
							L.close();
							Pipe_UpdateUI.close();
							exit(1);
							break;

						default:
							break;
						}

					}
				}

			}
			break;

			case EXAMINEPATHFILE:
				StopwordsNamePath = p.getMessageFromGraphics();
				break;

			case EXAMINESTOPWORDFILE:			
				fileNamePath = p.getMessageFromGraphics();
				break;

			case NGRAMSIZE:
				NgramSize = stoi(p.getMessageFromGraphics().c_str());
				break;

			case SEGMENTSIZE:
				segSize = stoi(p.getMessageFromGraphics().c_str());
				break;

			case CHOSENRUN:
				{
				string ChosenRunStr = p.getMessageFromGraphics();
				if (ChosenRunStr == "Dynamical")
					ChosenAprroachModel = DS_Aprroach;
				else if (ChosenRunStr == "Clustered")
					ChosenAprroachModel = CL_Aprroach;
				else 
					ChosenAprroachModel = Both_Aprroaches;
				break;
				}

			case PREFEREDCLUSTERSNUMBER:
			{
				string PreferedClusteresNumberStr = p.getMessageFromGraphics();
				if (PreferedClusteresNumberStr == "Examine in algorithm")
					PreferedClustersNumber = 0;
				else 
					PreferedClustersNumber = stoi(PreferedClusteresNumberStr.c_str());
				break;
			}

			case QUIT:
				exit(1);
				break;

			default:
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
				break;
			}

		}

	}


}