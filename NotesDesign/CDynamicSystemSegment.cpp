#include "CDynamicSystemSegment.h"

/*default copy c'tor*/
CDynamicSystemSegment::CDynamicSystemSegment(const CDynamicSystemSegment& origin) : CSegment(*this)
{
}

CDynamicSystemSegment::CDynamicSystemSegment(string  SegmentData, int NgramSize, vector<string>& vDictionary)
	: CSegment(SegmentData, NgramSize, vDictionary)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}


CDynamicSystemSegment::~CDynamicSystemSegment()
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

string & CDynamicSystemSegment::GetSegmentTmFileName(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		return msSegmentTmFileName;

	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CDynamicSystemSegment::SetSegmentTmFileName(string & FileName)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		msSegmentTmFileName = FileName;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

double CDynamicSystemSegment::GetApproximationError(void)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		return mfApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

void CDynamicSystemSegment::SetApproximationError(double ApproximationError)
{
	try {
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		mfApproximationError = ApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}

