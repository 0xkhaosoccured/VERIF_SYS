#define _AMD64_
#include "include/pch.h"
#include "include/logging.hpp"
#include <fileapi.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <fstream>

constexpr bool __debug = true;
std::vector<std::string> IAC = {}; 

const int  __getvsn__(std::vector<std::string> &IAC) 
{
  try {
    char buffer[MAX_PATH]; DWORD sysbuffer; DWORD vsn; DWORD filesf;
    if(GetVolumeInformationA("C:\\", buffer, sizeof(buffer), &vsn, &sysbuffer, &filesf, 0, 0)) {
      if constexpr(__debug) {logSuccess("Volume Succesfully found and VSN Extracted. . .");}
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
  if constexpr(__debug) {
    glLogger.enableFLOG();
  }
  __getvsn__(IAC);
  for(auto c : IAC) {
    std::cout << "IAC CONFIGURATION: " << c << std::endl;
  }
  std::cin.get();

}