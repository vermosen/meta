#pragma once
#ifndef META_DETECT_H
#define META_DETECT_H

#include <type_traits>

namespace meta {

  template< class... >
  using void_t = void;

  struct nonesuch {
    nonesuch() = delete;
    ~nonesuch() = delete;
    nonesuch(nonesuch const&) = delete;
    void operator=(nonesuch const&) = delete;
  };

namespace details {

  template <
      class Default
    , class AlwaysVoid
    , template<class...> class Predicate
    , class... Args
  > struct detect {
    using type = Default;
  };

  template <
      class Default
    , template<class...> class Predicate
    , class... Args
  > struct detect<Default, void_t<Predicate<Args...>>, Predicate, Args...> {
    using type = Predicate<Args...>;
  };

} // namespace detail

  template <template<class...> class Predicate, class... Args>
  struct detect {
    using type = typename details::detect<nonesuch, void, Predicate, Args...>::type;
  };

  template <template<class...> class Predicate, class Return, class... Args>
  struct has_method {
    using type = typename std::is_same<Return, typename detect<Predicate, Args...>::type>;
  };
}

#endif