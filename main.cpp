#define _AMD64_
#include "include/pch.h"
#include "include/logging.hpp"
#include "include/threads.hpp"

constexpr bool __debug = true;
std::vector<std::string> IAC = {}; 

const int  __getvsn__(std::vector<std::string> &IAC) 
{
  try {
    char buffer[MAX_PATH]; DWORD sysbuffer; DWORD vsn; DWORD filesf;
    if(GetVolumeInformationA("C:\\", buffer, sizeof(buffer), &vsn, &sysbuffer, &filesf, 0, 0)) {
      if constexpr(__debug) {logSuccess("Volume found and VSN extracted. . .");}
      IAC.push_back(std::to_string(vsn));
      return vsn;
    }
    throw std::logic_error("volume is not exist/found");
  } catch(const std::logic_error& exc) {
    logError(exc.what());
    return -1;
  }
  return -2;
}

int main() 
{
  int x = 1;
  if (x < 10) {
    logError("Something bad occured");
  }
  std::cin.get();
}