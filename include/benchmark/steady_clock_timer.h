#include <chrono>

struct steady_clock_timer {
  using clock = std::chrono::steady_clock;

  steady_clock_timer() : start(clock::now()) {}

  void restart() { start = clock::now(); }

  uint64_t nanoSeconds() const {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() -
                                                                start)
        .count();
  }

  double seconds() const { return nanoSeconds() * 1e-9; }

 private:
  clock::time_point start;
};