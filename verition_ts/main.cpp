#include <iostream>
#include "VTime.h"
#include "TimeSeries.h"


TimeSeries<int> t_series_from_string(std::string s){
    std::stringstream ss(s);
    std::string time;
    int hours, minutes, seconds;
    int value;
    TimeSeries<int> t_series;
    while (ss >> time){
        std::sscanf(time.c_str(), "%2d:%2d:%2d",
                    &hours,
                    &minutes,
                    &seconds);
//        std::cout<<hours << " " << minutes << " " << seconds<<std::endl;
        VTime t (hours * MICS_IN_HOUR + minutes * MICS_IN_MIN + seconds * MICS_IN_SEC);
//        std::cout << t.micSinceMidnight << std::endl;
        ss >> value;
        t_series.addValue(t.micSinceMidnight, value);
    }
    return t_series;
}

void run_test_sample(){
    std::string s = "09:00:00 0\n"
                    "09:30:00 1\n"
                    "09:31:00 2\n"
                    "09:32:00 3\n"
                    "09:35:00 4\n"
                    "09:40:00 5\n"
                    "09:45:00 6\n"
                    "09:50:00 7\n"
                    "10:00:00 8\n"
                    "10:10:00 9\n"
                    "10:11:00 10\n"
                    "10:12:00 11\n"
                    "10:15:00 12\n"
                    "10:20:00 13\n"
                    "10:30:00 14\n"
                    "10:41:00 15\n"
                    "10:52:00 16\n"
                    "10:55:00 17\n"
                    "11:00:00 18";
    auto t_series = t_series_from_string(s);
    std::cout<< "Sample Test" << std::endl;
    const auto sampled_t = t_series.sample(5 * MICS_IN_MIN);
    std::cout<< sampled_t <<std::endl;
}

void run_test_sample2(){
    std::string s ="09:30:00 1\n"
                    "09:31:00 2\n"
                    "10:41:00 15\n"
                    "10:52:00 16\n"
                    "10:55:00 17\n"
                    "11:00:00 18";
    auto t_series = t_series_from_string(s);
    const auto time_start = 32400000000; // 09:00:00
    const auto time_end = 39120000000; // 10:52:00
    std::cout<< "Sample2 Test - for default values before first date" << std::endl;
    const auto sampled_t2 = t_series.sample(5 * MICS_IN_MIN, time_start, time_end);
    std::cout<< sampled_t2 <<std::endl;
}

void run_test_sample3(){
    std::string s ="09:30:00 1\n"
                   "09:31:00 2\n"
                   "10:41:00 15";
    auto t_series = t_series_from_string(s);
    const auto time_start = 32400000000; // 09:00:00
    const auto time_end = 39120000000; // 10:52:00
    std::cout<< "Sample3 Test - for values after last date" << std::endl;
    const auto sampled_t2 = t_series.sample(5 * MICS_IN_MIN, time_start, time_end);
    std::cout<< sampled_t2 <<std::endl;
}


int main() {
    run_test_sample();
    run_test_sample2();
    run_test_sample3();
    return 0;
}