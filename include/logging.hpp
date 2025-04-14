#pragma once
#include "include/pch.h"

enum LogLvl {SUCCESS = 0, FAIL = 1};

const std::string WHITE = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";

inline std::string lvlcl[] = {
  "\033[32mSUCCESS\033[0m",
  "\033[31mERROR\033[0m"
};


namespace Logger 
{
  class Log
  {
    public:
    void logMessage(LogLvl lvl,const std::string& message)
    {
      std::time_t now = std::time(nullptr);
      std::tm* tm = std::localtime(&now);
      char timeStr[20];
      std::strftime(timeStr, sizeof(timeStr),"%H:%M:%S",tm);
      std::cerr << "[" << timeStr << "] "
                << lvlcl[lvl] << ": "
                << message << std::endl;
    }
  };
}

inline Logger::Log glLogger;

#define logSuccess(message) glLogger.logMessage(SUCCESS,message)
#define logError(message) glLogger.logMessage(FAIL, message)