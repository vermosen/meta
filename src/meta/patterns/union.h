#pragma once
#ifndef META_PATTERN_UNION_H
#define META_PATTERN_UNION_H

namespace meta    {
namespace details {

  template<
      typename L
    , typename R
  >
  struct union_cast_impl {

    static_assert(sizeof(L) == sizeof(R)
      , "Cannot cast types of different sizes");

    union {
      L m_left  ;
      R m_right ;
    };
  };
}

  template<
      typename L
    , typename R
  >
  inline L union_cast(R rhs) {
    details::union_cast_impl<L, R> ac; // clear -Werror=strict-aliasing
    ac.m_right = rhs;
    return ac.m_left;
  }
}

#endif // META_PATTERN_UNION_H
