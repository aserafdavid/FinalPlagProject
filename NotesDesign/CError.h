#ifndef CERROR_H
#define CERROR_H

#include <iostream>

using namespace std;

class CError
{
public:
	CError(string sError);
	void AddID(string sClass, string Function);
	void AddMsgToEnd(string Msg);
	string& GetErrMsg(void);

	CError& operator+= (string);

private:
	string msError;
};

#endif

