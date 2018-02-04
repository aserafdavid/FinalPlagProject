#include "CDynamicSystemSegment.h"

CDynamicSystemSegment& CDynamicSystemSegment::GetCDynamicSystemSegment(void)
{
	return *this;
}

/*default copy c'tor*/
CDynamicSystemSegment::CDynamicSystemSegment(const CDynamicSystemSegment& origin) :CSegment(*this)
{
	
}


CDynamicSystemSegment::CDynamicSystemSegment(string  SegmentData, int NgramSize,string pathTempFiles ,vector<string>& vDictionary)
	: CSegment(SegmentData, NgramSize, pathTempFiles, vDictionary)
{
	try {

	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}


CDynamicSystemSegment::~CDynamicSystemSegment()
{
}

void CDynamicSystemSegment::DivideIntoNgrams()
{
	try {
		CError Err(""); Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());
		int segSeize, jBlockOffset, iBlock = 0;
		string Curr_Block, tempNGram;

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

		SaveNgramDataToFile();//mvSegmentNgrams Conteain the Ngram for file saving
	
		CLogger::GetLogger()->Log("Block were Splited into Ngrams - createAnagramMatrix() Finished Succesfully");
	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
	}

void CDynamicSystemSegment::CalcTransitionMatrix(string FileToSPMat)
{
	try {

		arma::mat A, B;
		B.load(FileToSPMat);
		A.load(mfSegmentSPfileName);
		arma::mat X = arma::solve(A, B);

		string filename = mfSegmentNgramsfilepath;
		filename.append("\\TM's\\segTM" + std::to_string(miSegmentNumber) + ".txt");
		X.save(filename, arma::arma_ascii);
		msSegmentTmFileName = filename;
	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}

string CDynamicSystemSegment::GetSegmentTmFileName(void)
{
	try {

		return msSegmentTmFileName;

	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}

void CDynamicSystemSegment::SetSegmentTmFileName(string & FileName)
{
	try {
		CError Err(""); Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		CLogger::GetLogger()->Log(Err.GetErrMsg());

		msSegmentTmFileName = FileName;
	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}

double CDynamicSystemSegment::GetApproximationError(void)
{
	try {

		return mfApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}

void CDynamicSystemSegment::SetApproximationError(double ApproximationError)
{
	try {

		mfApproximationError = ApproximationError;
	}
	catch (CError& Err) {
		Err.AddID("CDynamicSystemSegment", __FUNCTION__);
		throw Err;
	}
}

