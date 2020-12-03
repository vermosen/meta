#pragma once
#ifndef META_CLOCK_H
#define META_CLOCK_H

#include <meta/traits/is_steady.h>

namespace meta   {
namespace clocks {

  // clock position
  enum class position {
      pre  = 0
    , post = 1
  };

  namespace details {
    template <typename T>
    struct defs;
  }
}

  template<typename Impl>
  struct clock : public clocks::details::defs<Impl> {

    using time_point_t = typename clocks::details::defs<Impl>::time_point_t;
    using duration_t   = typename clocks::details::defs<Impl>::duration_t;
    static constexpr bool is_steady = traits::is_steady<Impl>::value;

    static time_point_t now() noexcept {
      return time_point_t(Impl::now_impl());
    }
  };
}

#endif // META_CLOCK_H