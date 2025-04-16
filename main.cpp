#define _AMD64_
#include "include/pch.h"
#include "include/logging.hpp"

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
  // if constexpr(__debug) {
  //   glLogger.enableFLOG();
  // }
  // __getvsn__(IAC);
  // for(auto c : IAC) {
  //   std::cout << "IAC CONFIGURATION: " << c << std::endl;
  // }
  // std::cin.get();

  std::ifstream input("BREATH.aep", std::ios::binary);
  std::vector<Bytef> original_data((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
  uLong source_size = original_data.size();
  uLongf compress_buff_size = compressBound(source_size);
  std::vector<Bytef> compressed_data(compress_buff_size);

  int res = compress2(
      compressed_data.data(),  
      &compress_buff_size,      
      original_data.data(),     
      source_size,
      Z_BEST_COMPRESSION
  );

  std::cerr << std::setw(10) << "Original size:" 
          << std::setw(10) <<   source_size / (1024.0 * 1024.0)  
          << "MB" << std::endl;

  std::cerr << std::setw(10) << "Compressed size:" 
            << std::setw(10) <<  compress_buff_size / (1024.0 * 1024.0) 
            << "MB" << std::endl;
  
  
  std::cin.get();
}