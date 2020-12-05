#pragma once
#ifndef META_CLOCKS_DETAILS_TABLE_H
#define META_CLOCKS_DETAILS_TABLE_H

#include <meta/clocks/metric.h>
#include <meta/patterns/fold.h>

namespace meta    {
namespace clocks  {
namespace details {

  template <
      typename Clock
    , auto ... Keys
  >
  class table {
  public:
    using duration_t = typename Clock::duration;

  private:
    template <auto Key>
    using alias_t = metric<Clock, Key>;

    using fold_t = fold_enum<alias_t, Keys...>;

  public:
    void push(duration_t dur);

    template <auto Key>
    metric<Clock, Key>& get();

  private:
    fold_t m_fold;
  };

  template <typename Clock, auto ... Keys>
  void table<Clock, Keys ...>::push(duration_t dur) {
    (m_fold.template get<Keys>().update(dur), ...);
  }

  template <typename Clock, auto ... Keys>
  template <auto Key>
  metric<Clock, Key>& table<Clock, Keys ...>::get() { 
    return m_fold.template get<Key>(); 
  }
  
}}}

#endif // META_CLOCKS_DETAILS_TABLE_H
