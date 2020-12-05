#pragma once
#ifndef META_CLOCKS_DETAILS_TABLE_H
#define META_CLOCKS_DETAILS_TABLE_H

#include <meta/clocks/metric.h>

namespace meta    {
namespace clocks  {
namespace details {

  // TODO: can be made generic with an alias for the metric<Clock, T> obj;

  template <
      typename Clock
    , auto ... Keys
  >
  class table_impl;

  template <
      typename Clock
    , auto First
    , auto ... Rest
  >
  class table_impl<Clock, First, Rest ...> : public table_impl<Clock, Rest ...> {
  public:
    template <auto T>
    metric<Clock, T>& get() { 
      if constexpr (T == First) {
        return m_metric;
      } else {
        return table_impl<Clock, Rest ...>::template get<T>();
      }
    }

  private:
    metric<Clock, First> m_metric;
  };

  template <
      typename Clock
    , auto First
  >
  class table_impl<Clock, First> {
  public:
    using duration_t = typename Clock::duration;
  
  public:
    template <auto T>
    metric<Clock, T>& get() { 
      if constexpr (T == First) {
        return m_metric;
      } else {
        return std::nullopt;
      }
    }

  private:
    metric<Clock, First> m_metric;
  };

  template <
      typename Clock
    , auto ... Keys
  >
  class table : private details::table_impl<Clock, Keys ...> {
  public:
    using duration_t = typename Clock::duration;

    void push(duration_t dur);

    template <auto Key>
    metric<Clock, Key>& get();
  };

  template <typename Clock, auto ... Keys>
  void table<Clock, Keys ...>::push(duration_t dur) {
    (get<Keys>().update(dur), ...);
  }

  template <typename Clock, auto ... Keys>
  template <auto Key>
  metric<Clock, Key>& table<Clock, Keys ...>::get() { 
    return details::table_impl<Clock, Keys ...>::template get<Key>(); 
  }
  
}}}

#endif // META_CLOCKS_DETAILS_TABLE_H
