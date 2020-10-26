#pragma once
#ifndef META_CONCATENATE_H
#define META_CONCATENATE_H

#include <tuple>

namespace meta {

  template <typename T, typename K>
  struct concatenate;

  template <typename T, typename ... Args>
  struct concatenate<T, std::tuple<Args...>> {
    using type = std::tuple<T, Args...>;
  };
}

#endif // META_CONCATENATE_H