/*
 * VTime.h
 *
 *  Created on: Jun 20, 2017
 *      Author: mluk
 */

#ifndef DATAFEED_FLEX_VTIME_H_
#define DATAFEED_FLEX_VTIME_H_
#include <iostream>
#include <iomanip>
#include <sstream>

#define MICS_IN_SEC 1000L * 1000L
#define MICS_IN_MIN  60L *  MICS_IN_SEC
#define MICS_IN_HOUR  60L * MICS_IN_MIN

class VTime
{
    std::ostringstream o;
    bool ostringstreamSet = false;
public:
    uint64_t micSinceMidnight;

    uint64_t mics;
    uint64_t ms;
    uint64_t secs;
    uint64_t min;
    uint64_t hour;

    VTime(uint64_t mic)
        : micSinceMidnight(mic)
    {
        o.str("");

        mics = mic %1000;
        mic = mic / 1000;

        ms = mic % 1000;
        mic = mic / 1000;

        secs = mic % 60;
        mic= mic / 60;

        min = mic %60;
        mic= mic / 60;

        hour = mic;
    }

    std::string toHumanReadable()
    {
        if (ostringstreamSet)
            return o.str();
        else
        {
            ostringstreamSet = true;
            o << std::setfill('0') << std::setw(2) << hour << ':'
                    << std::setfill('0') << std::setw(2) << min << ':'
                    << std::setfill('0') << std::setw(2) << secs;
            return o.str();
        }
    }
};

#endif /* DATAFEED_FLEX_VTIME_H_ */
