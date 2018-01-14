#ifndef _CLogger_h_
#define _CLogger_h_


//#include <string>
#include "Utilities.h"

using namespace std;

#define LOGGER CLogger::GetLogger()

class CLogger
{
public:
	/**
	 Message message to be logged.
	*/
	void Log(const std::string& sMessage);
	/*
	format string for the message to be logged.
	*/
	void Log(const char * format, ...);
	/**
	   << overloaded function to Logs a message
	*/
	CLogger& operator<<(const string& sMessage);
	/**
	  Funtion to create the instance of logger class.
      return singleton object of Clogger class..
	*/
	static CLogger* GetLogger();

	static void SetLogPath(string path);

private:
	/**
	  Default constructor for the Logger class.
	*/
	CLogger();
	/**
	  copy constructor for the Logger class.
	*/
	CLogger(const CLogger&) {};             // copy constructor is private
									
											
	CLogger& operator=(const CLogger&) { return *this; };  // assignment operator is private

	/*
    Singleton logger class object pointer.
	*/
	static CLogger* m_pThis;
	/*
    Log file stream object.
	*/
	static ofstream m_Logfile;

};
#endif