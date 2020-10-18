#pragma once
#ifndef META_CPUCLOCK_H
#define META_CPUCLOCK_H

#include <ratio>
#include <chrono>
#include <iosfwd>

#include <meta/stopwatch.h>
#include <meta/pattern/alias.h>

namespace meta::clock {

  // duration type: cpu cycle has no subdivision
  using cycle = std::chrono::duration<std::int64_t, std::ratio<1>>;
}

namespace std::chrono {
  basic_ostream<char>& operator<<(
    basic_ostream<char>& os
    , duration<int64_t, ratio<1>> dur) {

    os << dur.count();
    return os;
  }
}

namespace meta::clock {

  // clock position
  enum class position {
    pre = 0
    , post = 1
  };

  namespace details {

    struct cpu_clock_defs {
      using duration = cycle;
      using rep = duration::rep;   // std::int64_t
      using period = duration::period;
      using time_point = std::chrono::time_point<cpu_clock_defs, duration>;

      static_assert(cpu_clock_defs::duration::min() < cpu_clock_defs::duration::zero()
        , "a clock's minimum duration cannot be less than its epoch");
    };

    std::basic_ostream<char>& operator<<(
      std::basic_ostream<char>& os
      , cpu_clock_defs::time_point tm) {
      os << tm.time_since_epoch();         // here, epoch is the cpu reset time
      return os;
    }

    template<typename Child>
    struct cpu_clock_base : public cpu_clock_defs {

      static constexpr bool is_steady = false;

      static time_point now() noexcept {
        return time_point(duration(Child::nowImpl()));
      }
    };
  }

  // the clock class
  template <clock::position Pos>
  struct cpu;

  template <>
  struct cpu<position::pre> : public details::cpu_clock_base<cpu<position::pre>> {
    static rep nowImpl() noexcept {
      unsigned clock[2] = { 0, 0 };
      STOPWATCH_PRE(clock[1], clock[0]);
      return *meta::alias_cast<rep*>(&clock);
    }
  };

  template <>
  struct cpu<position::post> : public details::cpu_clock_base<cpu<position::post>> {
    static rep nowImpl() noexcept {
      unsigned clock[2] = { 0, 0 };
      STOPWATCH_POST(clock[1], clock[0]);
      return *meta::alias_cast<rep*>(&clock);
    }
  };
}

#endif // META_CPUCLOCK_H