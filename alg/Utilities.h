#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

//#include <string>
#include "Logger.h"
#include <time.h>
#include <armadillo>



namespace Util
{
	using namespace arma;
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




}
#endif