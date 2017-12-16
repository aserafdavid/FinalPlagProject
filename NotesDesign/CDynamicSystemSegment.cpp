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
		miSegSize = SegmentData.size();
		DivideIntoNgrams();
		SaveNgramDataToFile();
	}
	catch (CError& Err) {
		Err.AddID("CText", __FUNCTION__);
		throw Err;
	}
}


CDynamicSystemSegment::~CDynamicSystemSegment()
{
		CError Err(""); Err.AddID("CText", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());
}

void CDynamicSystemSegment::DivideIntoNgrams()
{

	//Ngrams.empty();
	int segSeize, jBlockOffset, iBlock = 0;
	string Curr_Block, tempNGram;
	//for (int i = 0; i < textBlocks.size(); i++)// (!textBlocks[iBlock].empty())
	//{

	Curr_Block = msSegmentData;//textBlocks[iBlock++];
		segSeize = (int)Curr_Block.size();
		jBlockOffset = 0;
		while (Curr_Block[jBlockOffset] && Curr_Block[jBlockOffset + miNgramSize])
		{

			tempNGram = Curr_Block.substr(jBlockOffset, miNgramSize);
			if (!(std::find(mvDictionary.begin(), mvDictionary.end(), tempNGram) != mvDictionary.end()))
				mvDictionary.push_back(tempNGram);

			mvSegmentNgrams.push_back(tempNGram);
			jBlockOffset++;
		}
		/*Igonre the block leftover */
		//Ngrams.push_back(raw);

		SaveNgramDataToFile();//mvSegmentNgrams Conteain the Ngram for file saving
	
	CLogger::GetLogger()->Log("Block were Splited into Ngrams - createAnagramMatrix() Finished Succesfully");
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

