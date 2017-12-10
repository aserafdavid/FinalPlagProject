#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <time.h>
#include <fstream>
#include <armadillo>
//#include <fstream>
#include <iostream>
#include <cstdarg>

namespace
{
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


	static void removeSubstrs(string& s, string& p) {
		string::size_type n = p.length();
		for (string::size_type i = s.find(p); i != string::npos; i = s.find(p))
			s.erase(i, n);
	}
}
#endif