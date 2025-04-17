#pragma once
#include "include/pch.h"

enum LogLvl {SUCCESS = 0, FAIL = 1};

inline std::string lvlcl[] = {
  "\033[32mSUCCESS\033[0m",
  "\033[31mERROR\033[0m"
};

namespace Logger
{
  class Log
  {
    public:
      
      void logWrapper(LogLvl lvl,const std::string& message) 
      {
        std::thread th(&Log::logMessage, this, lvl, message);
        th.join();
      }

      void enableFLOG() 
      {
        logFile.open("logs.txt");
        isFOP = true;
      }
      void closeFLOG() 
      {
        if(logFile.is_open()){
          logFile.close();
        }
        isFOP = false;
      }

      ~Log() 
      {
        closeFLOG();
      }

    private:
      bool isFOP = false;
      std::ofstream logFile;
      std::mutex mtx;

      void logMessage(LogLvl lvl,const std::string& message)
      {
        std::lock_guard<std::mutex> lock(mtx);
        std::time_t now; std::tm* tm; std::string logLine;

        now = std::time(nullptr);
        tm = std::localtime(&now);
        char timeStr[20];
        std::strftime(timeStr, sizeof(timeStr),"%H:%M:%S",tm);
        logLine = "[" + std::string(timeStr) + "] " + lvlcl[lvl] + ": " + message;
        std::cerr << logLine << std::endl;
        if(isFOP && logFile.is_open()) {
          logFile << logLine << std::endl;
        }
      }
  };
}

inline Logger::Log glLogger;

#define logSuccess(message) glLogger.logWrapper(SUCCESS,message)
#define logError(message) glLogger.logWrapper(FAIL, message)