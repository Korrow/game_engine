// Copyright 2014 Keegan Morrow

#include <string>
#include <iomanip>
#include "core/logger_manager.hpp"
#include "core/logging.hpp"

namespace core{
LoggerManager::LoggerManager(int argv, char* argc[]){
    START_EASYLOGGINGPP(argv, argc);
}

bool LoggerManager::loadConfig(std::string configpath){
    LOG(INFO) << "Loading logging configuration from " << configpath;
    el::Configurations conf(configpath);
    el::Loggers::reconfigureAllLoggers(conf);
    return true;
}
}
