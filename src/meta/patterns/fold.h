#pragma once
#ifndef META_PATTERN_FOLD_H
#define META_PATTERN_FOLD_H

#include <optional> // std::nullopt

namespace meta {

  /*!
   * folds a collection of enums into some iterable structure
   */
  template <
      template <auto> typename Alias
    , auto ... Keys
  >
  class fold_enum;

namespace details {
  template <
      template <auto> typename Alias
    , auto ... Keys
  > 
  class fold_enum_impl;

  template <
      template <auto> typename Alias
    , auto First
    , auto ... Rest
  > 
  class fold_enum_impl<Alias, First, Rest...> : public fold_enum_impl<Alias, Rest...> {
  public:
    template <auto Key>
    Alias<Key>& get() { 
      if constexpr (Key == First) {
        return m_item;
      } else {
        return fold_enum_impl<Alias, Rest...>::template get<Key>();
      }
    }
  private:
    Alias<First> m_item;
  };

  template <
      template <auto> typename Alias
    , auto First
  > 
  class fold_enum_impl<Alias, First> {
  public:
    template <auto Key>
    Alias<Key>& get() { 
      if constexpr (Key == First) {
        return m_item;
      } else {
        std::nullopt; // meant to fail to compile (mismatch in type)
      }
    }
  private:
    Alias<First> m_item;
  };
}

  template <
      template <auto> typename Alias
    , auto ... Keys
  >
  class fold_enum : public details::fold_enum_impl<Alias, Keys...> {
  public:
    template <auto Key>
    Alias<Key>& get() {
      return details::fold_enum_impl<Alias, Keys...>::template get<Key>();
    }
  };
}

#endif // META_PATTERN_FOLD_H
