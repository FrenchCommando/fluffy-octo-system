/*
 * TimeSeries.h
 *
 *  Created on: Jun 20, 2017
 *      Author: mluk
 */

#ifndef CHALLENGE_TIMESERIES_H_
#define CHALLENGE_TIMESERIES_H_

#include <vector>
#include <stdexcept>
#include <iostream>
#include "VTime.h"
#include <limits>

template<typename>
struct default_value;

template<>
struct default_value<int> {
   static constexpr int value = 0;
};

template<>
struct default_value<double> {
   static constexpr double value = std::numeric_limits<double>::quiet_NaN();
};

template <typename T>
class TimeSeries
{
public:
    std::vector<uint64_t> timeUsSinceMid;
    std::vector<T> values;

    void addValue(uint64_t time, T value)
    {
        timeUsSinceMid.push_back(time);
        values.push_back(value);
    }
    int size() const
    {
        return values.size();
    }

    /*
     *
     *
     * @param sampleFreq
     * @param startTime
     * @return
     */
    TimeSeries<T> sample(uint64_t sampleFreq, uint64_t startTime, uint64_t endTime)
    {
        TimeSeries<T> t_series;
        auto current_time = startTime;
        const auto front_ptr = timeUsSinceMid.cbegin();
        const auto back_ptr = timeUsSinceMid.cend();
        auto current_ptr = std::lower_bound(front_ptr, back_ptr, current_time);
        while (current_time <= endTime){
            current_ptr = std::lower_bound(current_ptr, back_ptr, current_time);
            if(current_ptr == back_ptr)
            {
                const auto last_value = values.back();
                while (current_time <= endTime){
                    t_series.addValue(current_time, last_value);
                    current_time += sampleFreq;
                }
                break; // just add the next dates with the same values
            }

            const auto i = std::distance(front_ptr, current_ptr);
            if(i == 0){
                if (current_time == timeUsSinceMid.front()){
                    t_series.addValue(current_time, values.front());
                    current_time += sampleFreq;
                    continue;
                }
                const auto first_value = default_value<T>::value;
                while (current_time < timeUsSinceMid.front()){
                    t_series.addValue(current_time, first_value);
                    current_time += sampleFreq;
                }
                continue;
            }
            if(current_time == timeUsSinceMid[i])
                t_series.addValue(current_time, values[i]);
            else
                t_series.addValue(current_time, values[i - 1]);
            current_time += sampleFreq;
        }
        return t_series;

    }

    TimeSeries<T> sample(uint64_t sampleFreq)
    {
        return sample(sampleFreq, timeUsSinceMid.front(), timeUsSinceMid.back());
    }

};



template <typename T>
inline std::ostream& operator<<( std::ostream& out, const TimeSeries <T>& o  )
{
    for (int i = 0; i < o.size(); i++)
    {
        VTime v(o.timeUsSinceMid[i]);
        out << v.toHumanReadable()   << " " << o.values[i] << std::endl;
    }
    return out;
}

#endif 
