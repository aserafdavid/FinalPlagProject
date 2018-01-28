#include "Logger.h"
//#include"Utilities.h"

CLogger* CLogger::m_pThis = NULL;
ofstream CLogger::m_Logfile;
static string m_sFileName = "Log.txt";

CLogger::CLogger()
{

}

CLogger* CLogger::GetLogger() {
	if (m_pThis == NULL) {
		m_pThis = new CLogger();
		m_Logfile.open(m_sFileName.c_str(), ios::out | ios::app);
	}
	return m_pThis;
}

void CLogger::SetLogPath(string path)
{
	path.append("//Log.txt");
	m_sFileName = path;
}

void CLogger::Log(const char * format, ...)
{
	char* sMessage = NULL;
	int nLength = 0;
	va_list args;
	va_start(args, format);
	//  Return the number of characters in the string referenced the list of arguments.
	// _vscprintf doesn't count terminating '\0' (that's why +1)
	nLength = _vscprintf(format, args) + 1;
	sMessage = new char[nLength];
	vsprintf_s(sMessage, nLength, format, args);
	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	va_end(args);

	delete[] sMessage;
}

void CLogger::Log(const string& sMessage)
{
	m_Logfile << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
}

CLogger& CLogger::operator<<(const string& sMessage)
{
	m_Logfile << "\n" << CurrentDateTime() << ":\t";
	m_Logfile << sMessage << "\n";
	return *this;
}