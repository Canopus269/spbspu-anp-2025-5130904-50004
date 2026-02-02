#include "tasks.hpp"

#include <iostream>

int main()
{
  seq::Results results;
  int exitCode = 0;

  if (!seq::processSequence(std::cin, results))
  {
    std::cerr << "invalid input sequence\n";
    return 1;
  }

  std::cout << results.incSeq << "\n";

  if (results.sumDupOk)
  {
    std::cout << results.sumDup << "\n";
  }
  else
  {
    std::cerr << "cannot calculate sequence characteristic\n";
    exitCode = 2;
  }

  return exitCode;
}
