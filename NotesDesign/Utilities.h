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

namespace
{
#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)
#define INVALID_SET_FILE_POINTER ((DWORD)-1)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

	//using namespace arma;
	using namespace std;
	// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
	const std::string CurrentDateTime()
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

	//static bool SaveNgramDataToFile(ofstream output, vector<string> vSegmentNgrams)
	//{
	//	if (!output.is_open())
	//		return false;

	//	for each (string Ngram in vSegmentNgrams)
	//		output << Ngram << endl;
	//	return true;
	//}

	/*remove to Setinfrastructure function */
	static bool Setinfrastructure(void)
	{
		if (!dirExists("tempFiles"))
		{
			mkdir("tempFiles");
			mkdir("tempFiles/CFM's");
			mkdir("tempFiles/SegNgrams");
		}
		if (!dirExists("tempFiles/CFM's"))
			mkdir("tempFiles/CFM's");
		if (!dirExists("tempFiles/SegNgrams"))
			mkdir("tempFiles/SegNgrams");

		if (!dirExists("tempFiles/CFM's") || !dirExists("tempFiles/SegNgrams"))
			return false;
		return true;
	}
}
#endif