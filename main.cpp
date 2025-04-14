#define _AMD64_
#include <iostream>
#include <fileapi.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

constexpr bool __debug = true;
std::vector<std::string> IAC = {}; 

const int  __getvsn__(std::vector<std::string> &IAC) 
{
  try {
    char buffer[MAX_PATH]; DWORD sysbuffer; DWORD vsn; DWORD filesf;
    if(GetVolumeInformationA("C:\\", buffer, sizeof(buffer), &vsn, &sysbuffer, &filesf, 0, 0)) {
      if constexpr(__debug) {std::cerr << "\033[32mVolume ID: \033[0m " << vsn << std::endl;}
      IAC.push_back(std::to_string(vsn));
      return vsn;
    } 
    throw std::logic_error("volume is not exist/found");
  } catch(const std::logic_error& exc) {
  
    // TODO: Add here future logging func (Logi nyzhno tozhe delatb ny za chto)

    std::cerr << "\033[31m" << exc.what() << "\033[0m" << std::endl;
  }
}



int main() 
{
  __getvsn__(IAC);
  for(auto c : IAC) {
    std::cout << "IAC CONFIGURATION: " << c << std::endl;
  }

}