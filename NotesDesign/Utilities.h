#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <time.h>
#include <fstream>
#include <armadillo>
//#include <fstream>
#include <iostream>
#include <cstdarg>
#include <direct.h>
#include <windows.h>

typedef enum {
	DS_Aprroach,
	CL_Aprroach,
	Both_Aprroaches
} AprroachModel;

namespace
{
#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

	//using namespace arma;
	using namespace std;
	static string Global_PathToTempFiles;

	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	//const std::string CurrentDateTime()
	std::string CurrentDateTime()
	{
		time_t     now = time(NULL);
		struct tm  tstruct;
		char       buf[80];
		localtime_s(&tstruct, &now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
		return buf;
	}

	static volatile unsigned int GetSegId()
	{
		static unsigned int ID = 0;
		return ID++;
	}

	/*responsibility of remove files from last run is on the main */
	/*Double "Slash" for example ""c:\\CFM's\\*.txt"" */
	static void DeleteAllFilesInFolder(string path)
	{
		std::string command = "del /Q ";
		system(command.append(path).c_str());
	}

	static void removeSubstrs(string& s, string& p) {
		string::size_type n = p.length();
		for (string::size_type i = s.find(p); i != string::npos; i = s.find(p))
			s.erase(i, n);
	}

	static bool dirExists(const std::string& dirName_in)
	{

		DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!

		return false;    // this is not a directory!
	}

	static void SaveNgramDataToFile(ofstream output, vector<string> vSegmentNgrams)
	{
		if (!output.is_open())
		{
			
		}

		for each (string Ngram in vSegmentNgrams)
			output << Ngram << endl;
		
	}

	/*remove to Setinfrastructure function */
	static bool Setinfrastructure(string* TempFilesPath)
	{
		string tempFiles = *TempFilesPath;
		tempFiles.append("tempFiles");
		//Remove temp directory before generate new files;
		//_rmdir(tempFiles.c_str());
		const char* path = tempFiles.c_str();
		//verify tempFiles directory exist
		if (!dirExists(tempFiles))
			_mkdir(path);

		if ( !dirExists(tempFiles) )
			return false;

		//change version Path to adapt directory name format
		string versionPath = tempFiles.append("\\" + CurrentDateTime());
		replace(versionPath.begin() +3, versionPath.end(), ':', '_');
		replace(versionPath.begin(), versionPath.end(), '-', '_');
		replace(versionPath.begin(), versionPath.end(), '.', '-');

		//create all sub directories
		if (!dirExists(versionPath))
		{
			_mkdir(versionPath.c_str());
			tempFiles = versionPath;
			tempFiles.append("//CFM's");
			_mkdir(tempFiles.c_str());
			tempFiles = versionPath;
			tempFiles.append("//SegNgrams");
			_mkdir(tempFiles.c_str());
			tempFiles = versionPath;
			tempFiles.append("//SP's");
			_mkdir(tempFiles.c_str());
			tempFiles = versionPath;
			tempFiles.append("//TM's");
			_mkdir(tempFiles.c_str());
			tempFiles = versionPath;
			tempFiles.append("//Results");
			_mkdir(tempFiles.c_str());
		}

		//verrify all sub directories exists
		if (!dirExists(versionPath) ||
			!dirExists(versionPath + "//CFM's") ||
			!dirExists(versionPath +"//SegNgrams") ||
			!dirExists(versionPath + "//SP's") ||
			!dirExists(versionPath + "//TM's") ||
			!dirExists(versionPath + "//Results") )
			return false;

		///*remove  last run files*/
		//DeleteAllFilesInFolder("c:\\CFM's\\*.txt");
		//DeleteAllFilesInFolder("c:\\CFM's\\*.txt");

		*TempFilesPath = versionPath;
		return true;
	}

}
#endif