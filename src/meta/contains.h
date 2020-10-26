#pragma once
#ifndef META_CONTAINS_H
#define META_CONTAINS_H

#include <type_traits>

namespace meta {

  template <typename T, typename ... Args>
  struct contains {
    static constexpr bool value = (std::is_same<Args, T>::value || ...);
  };
}

#endif // META_CONTAINS_H