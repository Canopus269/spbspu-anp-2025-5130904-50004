#include "str_ops.hpp"
#include <cctype>

namespace
{

static void markLatinLetters(const char* s, unsigned char present[26]) noexcept
{
  if (s == nullptr) {
    return;
  }

  size_t i = 0;
  while (s[i] != '\0') {
    const unsigned char uc = static_cast<unsigned char>(s[i]);
    if (std::isalpha(uc) != 0) {
      const unsigned char lc =
        static_cast<unsigned char>(std::tolower(uc));
      if ((lc >= static_cast<unsigned char>('a')) &&
          (lc <= static_cast<unsigned char>('z'))) {
        present[static_cast<size_t>(lc - static_cast<unsigned char>('a'))] = 1;
      }
    }
    ++i;
  }
}

}

size_t oztas::cstrLen(const char* s) noexcept
{
  if (s == nullptr) {
    return 0;
  }

  size_t n = 0;
  while (s[n] != '\0') {
    ++n;
  }
  return n;
}

size_t oztas::replaceSymbol(
  const char* src,
  int fromCh,
  int toCh,
  char* dst,
  size_t dstSize
) noexcept
{
  const size_t n = oztas::cstrLen(src);
  if ((dst == nullptr) || (dstSize < (n + 1))) {
    return n;
  }

  const char from = static_cast<char>(fromCh);
  const char to = static_cast<char>(toCh);

  for (size_t i = 0; i < n; ++i) {
    const char c = src[i];
    if (c == from) {
      dst[i] = to;
    } else {
      dst[i] = c;
    }
  }

  dst[n] = '\0';
  return n;
}

size_t oztas::latinTwo(
  const char* s1,
  const char* s2,
  char* dst,
  size_t dstSize
) noexcept
{
  unsigned char present[26] = {0};

  markLatinLetters(s1, present);
  markLatinLetters(s2, present);

  size_t need = 0;
  for (size_t i = 0; i < 26; ++i) {
    if (present[i] != 0) {
      ++need;
    }
  }

  if ((dst == nullptr) || (dstSize < (need + 1))) {
    return need;
  }

  size_t pos = 0;
  for (size_t i = 0; i < 26; ++i) {
    if (present[i] != 0) {
      dst[pos] = static_cast<char>('a' + i);
      ++pos;
    }
  }

  dst[pos] = '\0';
  return need;
}
