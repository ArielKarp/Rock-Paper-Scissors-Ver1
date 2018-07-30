/*
 * Logger.cpp
 *
 *  Created on: Apr 20, 2018
 *      Author: ariel
 */


#include "Logger.h"
#include "Utilities.h"

const std::string CLogger::m_sFileName = "Log.txt";
CLogger* CLogger::m_pThis = NULL;
std::ofstream CLogger::m_Logfile;

CLogger::CLogger()
{

}
CLogger* CLogger::GetLogger(){
    if (m_pThis == NULL){
        m_pThis = new CLogger();
        m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
    }
    return m_pThis;
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
    vsnprintf(sMessage, nLength, format, args);
    //vsprintf(sMessage, format, args);
    m_Logfile << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    va_end(args);

    delete [] sMessage;
}

void CLogger::Log(const std::string& sMessage)
{
    m_Logfile <<  Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
}

CLogger& CLogger::operator<<(const std::string& sMessage)
{
    m_Logfile << "\n" << Util::CurrentDateTime() << ":\t";
    m_Logfile << sMessage << "\n";
    return *this;
}

int CLogger::_vscprintf (const char * format, va_list pargs) {
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
 }
