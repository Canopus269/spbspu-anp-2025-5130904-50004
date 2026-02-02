#ifndef TASKS_HPP
#define TASKS_HPP

#include <cstddef>
#include <iosfwd>

namespace seq {

  struct Results
  {
    long long incSeq;
    long long sumDup;
    std::size_t count;
    bool sumDupOk;
  };

  bool processSequence(
    std::istream& input,
    Results& results
  );

}

#endif
