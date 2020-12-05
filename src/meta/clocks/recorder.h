#pragma once
#ifndef META_CLOCKS_RECORDER_H
#define META_CLOCKS_RECORDER_H

#include <meta/clocks/details/table.h>

namespace meta   {
namespace clocks {

  template <
      typename Clock
    , metrics::type ... Keys
  >
  class recorder;
  
  template <
      typename Clock
    , metrics::type ... Keys
  >
  std::ostream& operator<<(std::ostream&, const recorder<Clock, Keys...>&); // silent gcc warnings

  template <
      typename Clock
    , metrics::type ... Keys
  >
  class recorder {
  public:
    using duration_t = typename Clock::duration;
    using table_t = details::table<Clock, Keys ...>;
  public:
    recorder();
    void push(duration_t dur);

    friend std::ostream& operator << <>(std::ostream&, const recorder<Clock, Keys...>&);
  private:
    table_t m_table;
  };
  
  template <typename Clock, metrics::type ... Keys>
  inline recorder<Clock, Keys ...>::recorder() {}

  template <typename Clock, metrics::type ... Keys>
  inline void recorder<Clock, Keys ...>::push(duration_t dur) {
    m_table.push(dur);
  }

  template <class Clock, metrics::type ... Keys>
  inline std::ostream& operator <<(std::ostream& os, const recorder<Clock, Keys...>& o) {
    //os << o.m_table;
    return os;
  }

}}

#endif // META_CLOCKS_RECORDER_H
