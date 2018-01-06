#ifndef SegmentClustered_H
#define SegmentClustered_H

/* includes */
//#include <vector>
//#include <iostream>
//#include <fstream>
//#include "Logger.h"
//#include "CError.h"
//#include "CAlgorithms.h"

//using namespace std;
#include "CSegment.h"
#include "CDynamicSystemSegment.h"
#include "CAlgorithms.h"

/* class definition */
class CClusteredSegment : public CSegment
{
public:
	CClusteredSegment& GetCDynamicSystemSegment(void);
	CClusteredSegment(const CClusteredSegment& origin);
	CClusteredSegment(const CDynamicSystemSegment& origin);

	CClusteredSegment(string SegmentData, int NgramSize, string pathTempFiles, vector<string>& vDictionary);
	~CClusteredSegment();

	arma::vec CalcEV(void);

protected:

private:

};
#endif

