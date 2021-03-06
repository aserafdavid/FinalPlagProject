
#pragma region Includes
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>
#pragma endregion



enum pipe_in {  /*messages from the UI*/
	EXAMINEPATHFILE/**/
	, EXAMINESTOPWORDFILE
	, NGRAMSIZE
	, SEGMENTSIZE
	, STARTWORK
	, QUIT
	, CANCELRUN
	, CHOSENRUN
	, PREFEREDCLUSTERSNUMBER
};

enum pipe_out {
	Initialize
	, OmitStopWordsStepFinished
	, DevideTextToSegStepFinished
	, ExtractNgramsStepFinished
	, BuildVocStepFinished
	, BuldCFMsStepFinished
	, BuildSPsStepFinished

	, BuildQsStepFinished
	, CalcAQMeasureStepFinished
	, CalcApproxMeasStepFinished
	, ExamineResult

	, EvmCreationFinished
	, ClusterizationFinished
	, ExamineCLResult

	, FinishLoadingStage
	, CancelRUN
};


#define Color_Red "\33[0:31m\\]" // Color Start
#define Color_end "\33[0m\\]" // To flush out prev settings
#define LOG_RED(X) printf("%s %s %s",Color_Red,X,Color_end)

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

using namespace std;

#define BUFFER_SIZE		1024 // 1K
#define PIPEMAINNAME "\\\\.\\pipe\\PlagPipe"
#define PIPELOADNAME "\\\\.\\pipe\\PIPELOADNAME"
#define PIPEUPDATEUI "\\\\.\\pipe\\PIPEUPDATEUI"
 class Pipe
{
private:

	LPTSTR  strPipeName;

public:

	HANDLE hPipe;
	void Pipe::Test();
	Pipe(int pipeType)
	{
		if (pipeType == 0)
			strPipeName = TEXT(PIPEMAINNAME);
		else if(pipeType == 1)
			strPipeName = TEXT(PIPELOADNAME);
		else if (pipeType ==2)
			strPipeName = TEXT(PIPEUPDATEUI);

	}
	
	bool connect()
	{
		hPipe = CreateFile(
			strPipeName,			// Pipe name 
			GENERIC_READ |			// Read and write access 
			GENERIC_WRITE | PIPE_WAIT |PIPE_ACCESS_DUPLEX,
			1,						// No sharing 
			NULL,					// Default security attributes
			OPEN_EXISTING,			// Opens existing pipe 
			0,						// Default attributes 
			NULL);					// No template file 

									// Break if the pipe handle is valid. 
		if (hPipe != INVALID_HANDLE_VALUE)
			return true;

		if (// Exit if an error other than ERROR_PIPE_BUSY occurs
			GetLastError() != ERROR_PIPE_BUSY
			||
			// All pipe instances are busy, so wait for 5 seconds
			!WaitNamedPipe(strPipeName, 5000))
		{
			//system("COLOR 74");
			_tprintf(_T("Unable to open named pipe %s w/err 0x%08lx\n"),
				strPipeName, GetLastError());
			return false;
		}

		_tprintf( _T( " The named pipe, %s, is connected.\n"), strPipeName );
		return true;

	}

	bool sendMessageToGraphics(char* msg)
	{
		char* chRequest = msg;	// Client -> Server
		DWORD cbBytesWritten, cbRequestBytes;

		// Send one message to the pipe.

		cbRequestBytes = sizeof(TCHAR) * (lstrlen(chRequest) + 1);
		
		BOOL bResult = WriteFile(			// Write to the pipe.
			hPipe,						// Handle of the pipe
			chRequest,					// Message to be written
			cbRequestBytes,				// Number of bytes to write
			&cbBytesWritten,			// Number of bytes written
			NULL);						// Not overlapped 

		if (!bResult/*Failed*/ || cbRequestBytes != cbBytesWritten/*Failed*/)
		{
			_tprintf( _T( "WriteFile failed w/err 0x%08lx\n"), GetLastError());
			return false;
		}

		_tprintf( _T( "Sends %ld bytes; Message: \"%s\"\n"),
			cbBytesWritten, chRequest);

		return true;

	}

	string getMessageFromGraphics()
	{
		DWORD cbBytesRead;
		DWORD cbReplyBytes;
		TCHAR chReply[BUFFER_SIZE];		// Server -> Client

		cbReplyBytes = sizeof(TCHAR) * BUFFER_SIZE;
		BOOL bResult = ReadFile(			// Read from the pipe.
			hPipe,					// Handle of the pipe
			chReply,				// Buffer to receive the reply
			cbReplyBytes,			// Size of buffer 
			&cbBytesRead,			// Number of bytes read 
			NULL);					// Not overlapped 

		if (!bResult && GetLastError() != ERROR_MORE_DATA)
		{
			_tprintf( _T( "ReadFile failed w/err 0x%08lx\n"), GetLastError());
			return "";
		}

		_tprintf( _T( "Receives %ld bytes; Message: \"%s\"\n"),
			cbBytesRead, chReply);

		return chReply;

	}

	void close()
	{
		CloseHandle(hPipe);
	}


};
