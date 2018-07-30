/*
 * Utilities.h
 *
 *  Created on: Apr 20, 2018
 *      Author: ariel
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <string>
#include <time.h>

namespace Util
{
    // Get current date/time, format is YYYY-MM-DD.HH:mm:ss
    const std::string CurrentDateTime()
    {
        time_t     now = time(NULL);
        struct tm * tstruct;
        char       buf[80];
        tstruct = localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", tstruct);
        return buf;
    }
}

#endif /* UTILITIES_H_ */
