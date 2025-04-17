#include "include/pch.h"

std::mutex mtx;

void printSymb(char symb)
{
  std::lock_guard<std::mutex> lg(mtx);
  for(int i = 0; i < 3; ++i) {
    std::cout  << symb << std::endl; 
  } 
}

void doSmthTH() 
{
  std::thread th1(printSymb,'a');
  std::thread th2(printSymb,'b');
  th1.join();
  th2.join();
}

