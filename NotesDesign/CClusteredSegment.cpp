#include "CClusteredSegment.h"

CClusteredSegment & CClusteredSegment::GetCDynamicSystemSegment(void)
{
	return *this;
}

/*default copy c'tor*/
CClusteredSegment::CClusteredSegment(const CClusteredSegment& origin) 
	:CSegment(origin)
{

}

CClusteredSegment::CClusteredSegment(const CDynamicSystemSegment & src)
	: CSegment(src)
{
	try {
		CError Err(""); Err.AddID("CClusteredSegment", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

	}
	catch (CError& Err) {
		Err.AddID("CClusteredSegment", __FUNCTION__);
		throw Err;
	}
}

CClusteredSegment::CClusteredSegment(string  SegmentData, int NgramSize, string pathTempFiles, vector<string>& vDictionary)
	: CSegment(SegmentData, NgramSize, pathTempFiles, vDictionary)
{
	try {
		CError Err(""); Err.AddID("CClusteredSegment", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

	}
	catch (CError& Err) {
		Err.AddID("CClusteredSegment", __FUNCTION__);
		throw Err;
	}
}


CClusteredSegment::~CClusteredSegment()
{
	CError Err(""); Err.AddID("CClusteredSegment", __FUNCTION__);
	CLogger::GetLogger()->Log(Err.GetErrMsg());
}
