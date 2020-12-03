#pragma once
#ifndef META_CLOCKS_CPU_H
#define META_CLOCKS_CPU_H

#include <ratio>
#include <chrono>
#include <iosfwd>

#include <meta/clock.h>
#include <meta/asm/comment.h>
#include <meta/asm/stopwatch.h>
#include <meta/patterns/alias.h>

namespace meta::clocks {

  template <position>
  struct cpu;
}

namespace meta::traits {

  template <clocks::position Pos>
  struct is_steady<clocks::details::defs<clocks::cpu<Pos>>> {
    static constexpr bool value = false;
  };
}

namespace meta::clocks {
namespace details      {
  
  template <position Pos>
  struct defs<cpu<Pos>> {
    using duration_t   = std::chrono::duration<std::int64_t, std::ratio<1>> ;
    using rep          = duration_t::rep                                    ; // std::int64_t
    using period       = duration_t::period                                 ;
    using time_point_t = std::chrono::time_point<defs<cpu<Pos>>, duration_t>;

    static_assert(defs<cpu<Pos>>::duration_t::min() < defs<cpu<Pos>>::duration_t::zero()
      , "a clock's minimum duration cannot be less than its epoch");
  };
}
  template <position Pos>
  std::basic_ostream<char>& operator<<(
      std::basic_ostream<char>& os
    , typename details::defs<cpu<Pos>>::time_point tm) {
    os << tm.time_since_epoch();          // here, epoch is the cpu reset time
    return os;
  }

  template <>
  struct cpu<position::pre> : public clock<cpu<position::pre>> {
    static time_point_t now_impl() noexcept { 
      unsigned counter[2] = { 0, 0 };
      STOPWATCH_PRE(counter[1], counter[0]);
      ASM_COMMENT("CPUCLOCK PRE");
      return time_point_t(duration_t(*meta::alias_cast<rep*>(&counter)));
    }
  };

  template <>
  struct cpu<position::post> : public clock<cpu<position::post>> {
    static time_point_t now_impl() noexcept {
      unsigned counter[2] = { 0, 0 };
      ASM_COMMENT("CPUCLOCK POST");
      STOPWATCH_POST(counter[1], counter[0]);
      return time_point_t(duration_t(*meta::alias_cast<rep*>(&counter)));
    }
  };

  // overloaded diff operator
  // TODO: we could redefine a different return type to keep 
  // track of the fact we are dealing with a valid time diff,
  // per example measure<cpu>::duration_t
  details::defs<cpu<position::post>>::duration_t operator-(
      cpu<position::post>::time_point_t end
    , cpu<position::pre>::time_point_t start) {
    auto result = end.time_since_epoch() - start.time_since_epoch();
    return result;
  }
}

#endif // META_CLOCKS_CPU_H