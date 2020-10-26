#pragma once
#ifndef META_REMOVE_H
#define META_REMOVE_H

#include <type_traits>

#include <meta/concatenate.h>

namespace meta {

  /*!
   * remove an element from a variadic list
   */
  template <
    typename T
    , typename ... Args
  > struct remove;

  template <typename T, typename First, typename ... Args>
  struct remove<T, First, Args ... > {
    using type = typename std::conditional<!std::is_same<T, First>::value,
      typename concatenate<First, typename remove<T, Args...>::type>::type,
      typename remove<T, Args ...>::type
    >::type;
  };

  template <typename T>
  struct remove<T> {
    using type = std::tuple<>;
  };

  // tuple helper
  template <typename T, typename ... Args>
  struct remove<T, std::tuple<Args ...>> {
    using type = typename remove<T, Args...>::type;
  };
}

#endif // META_REMOVE_H