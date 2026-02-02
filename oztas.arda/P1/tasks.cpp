#include "tasks.hpp"

#include <istream>
#include <limits>

bool seq::processSequence(
  std::istream& input,
  Results& results
)
{
  results.incSeq = 0;
  results.sumDup = 0;
  results.count = 0;
  results.sumDupOk = false;

  bool hasPrev = false;
  int prev = 0;

  bool hasPrev1 = false;
  bool hasPrev2 = false;
  int prev1 = 0;
  int prev2 = 0;

  while (true)
  {
    long long value = 0;

    if (!(input >> value))
    {
      return false;
    }

    if (value < std::numeric_limits<int>::min()
      || value > std::numeric_limits<int>::max())
    {
      return false;
    }

    const int current = static_cast<int>(value);

    if (current == 0)
    {
      break;
    }

    if (hasPrev)
    {
      if (current > prev)
      {
        ++results.incSeq;
      }
    }

    prev = current;
    hasPrev = true;

    if (hasPrev1 && hasPrev2)
    {
      const long long sum =
        static_cast<long long>(prev1)
        + static_cast<long long>(prev2);

      if (static_cast<long long>(current) == sum)
      {
        ++results.sumDup;
      }
    }

    prev2 = prev1;
    hasPrev2 = hasPrev1;
    prev1 = current;
    hasPrev1 = true;

    ++results.count;
  }

  if (results.count >= 3)
  {
    results.sumDupOk = true;
  }

  return true;
}
