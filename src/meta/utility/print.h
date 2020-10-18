#pragma once
#ifndef META_UTILITY_PRINT_H
#define META_UTILITY_PRINT_H

#include <type_traits>

namespace meta {
  
  /*!
   * @brief a minimalist function to print class type at compile time
   */
  template<typename T>
  struct print {
    static_assert(std::is_same<T, int>::value && !std::is_same<T, int>::value
      , "Compilation failed because you wanted to read the type. See above");
  };
}

#endif // META_UTILITY_PRINT_H