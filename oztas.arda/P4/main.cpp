#include <iostream>
#include <new>
#include "str_ops.hpp"

int main()
{
  const size_t initialCap = 64;
  size_t cap = initialCap;
  size_t len = 0;

  char* input = new (std::nothrow) char[cap];
  if (input == nullptr) {
    std::cerr << "error: cannot allocate memory\n";
    return 1;
  }

  while (true) {
    const int ch = std::cin.get();
    if ((ch == '\n') || (ch == EOF)) {
      break;
    }

    if ((len + 1) >= cap) {
      const size_t newCap = cap * 2;
      char* newBuf = new (std::nothrow) char[newCap];
      if (newBuf == nullptr) {
        delete[] input;
        std::cerr << "error: cannot allocate memory\n";
        return 1;
      }

      for (size_t i = 0; i < len; ++i) {
        newBuf[i] = input[i];
      }

      delete[] input;
      input = newBuf;
      cap = newCap;
    }

    input[len] = static_cast<char>(ch);
    ++len;
  }

  input[len] = '\0';

  const size_t inputLen = oztas::cstrLen(input);

  char* out1 = new (std::nothrow) char[inputLen + 1];
  if (out1 == nullptr) {
    delete[] input;
    std::cerr << "error: cannot allocate memory\n";
    return 1;
  }

  oztas::replaceSymbol(input, 'c', 'b', out1, inputLen + 1);
  std::cout << out1 << "\n";

  const char* second = "def_ghk";
  const size_t maxLatinLetters = 26;
  const size_t out2Cap = maxLatinLetters + 1;

  char* out2 = new (std::nothrow) char[out2Cap];
  if (out2 == nullptr) {
    delete[] out1;
    delete[] input;
    std::cerr << "error: cannot allocate memory\n";
    return 1;
  }

  oztas::latinTwo(input, second, out2, out2Cap);
  std::cout << out2 << "\n";

  delete[] out2;
  delete[] out1;
  delete[] input;
  return 0;
}
