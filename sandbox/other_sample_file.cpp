//
// Created by frenchcommando on 6/7/2019.
//

#include <iostream>
#include <sstream>
#include <glog/logging.h>

void run_two(){
    FLAGS_log_dir = "/home/frenchcommando/logs";
    FLAGS_log_dir = "/mnt/c/Users/marti/CLionProjects/PersoTools/logs";
    FLAGS_logtostderr = 0;
    google::InitGoogleLogging("MyLog");
    LOG(INFO) << "I'm Here Too";
}