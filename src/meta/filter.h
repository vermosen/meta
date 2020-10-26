#pragma once
#ifndef META_FILTER_H
#define META_FILTER_H

#include <tuple>
#include <type_traits>

#include <meta/concatenate.h>

namespace meta {

  /*!
   * filters an element from a variadic list using a predicate
   */
  template <
    template <typename> typename Predicate
    , typename ... Args
  > struct filter;

  template <
    template <typename> typename Predicate
    , typename First
    , typename ... Args
  >
    struct filter<Predicate, First, Args ...> {
    using type = typename std::conditional<Predicate<First>::value,
      typename concatenate<First, typename filter<Predicate, Args...>::type>::type,
      typename filter<Predicate, Args...>::type
    >::type;
  };

  template <template <typename> typename Predicate>
  struct filter<Predicate> {
    using type = std::tuple<>;
  };
}

#endif // META_FILTER_H