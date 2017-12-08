#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <time.h>
#include <fstream>
#include <armadillo>
#include "Logger.h"


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


	static arma::Mat<int>* Create_CFM(const vector <string> NgramSeg, vector <string>* dictionary)
	{
		arma::Mat<int>* segCFM = new arma::Mat<int>(dictionary->size(), NgramSeg.size());
		segCFM->fill(0);
		for (int i = 0; i < NgramSeg.size(); i++)
		{
			//size_t pos = NgramSeg[i] - dictionary->begin();
			auto  pos = find(dictionary->begin(), dictionary->end(), NgramSeg[i]) - dictionary->begin();
			if (pos >= dictionary->size())
			{
				CLogger::GetLogger()->Log("There is an Ngram that exist in seg and doesn't exist in dictionary. found in Create_CFM()--> aborting");
				exit(1);
			}
			if (i == 0)
			{
				segCFM[i][pos]++;
			}
			else {
				segCFM->row(i) = segCFM->row(i + 1);/*copy last coloumn to the current one*/
				segCFM[i][pos]++;
			}
		}
		return segCFM;

	}

}
#endif