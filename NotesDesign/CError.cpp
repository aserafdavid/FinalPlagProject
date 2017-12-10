#include "CError.h"

CError::CError(string sError) :msError(sError) { }

void CError::AddID(string sClass, string Function)
{
	string newID;
	newID += sClass;
	newID += "::";
	newID += Function;
	newID += "-->";
	msError = newID;
}

void CError::AddMsgToEnd(string Msg)
{
	msError += Msg;
}

CError& CError::operator+= (string Err)
{
	msError += Err;
	return *this;
}

string& CError::GetErrMsg(void)
{
	return msError;
}

