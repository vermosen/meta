#pragma once
#ifndef META_CLOCKS_RECORDER_H
#define META_CLOCKS_RECORDER_H

namespace meta   {
namespace clocks {

  template <typename Clock>
  class recorder {
  public:
    using duration_type = typename Clock::duration;
    void add(duration_type dur) {
      m_stats += dur;
    }

    template<class T>
    friend std::ostream& operator <<(std::ostream&, const recorder<T>&);

  private:
    duration_type m_stats;
  };
  
  template <typename Clock>
  inline std::ostream& operator <<(std::ostream& os, const recorder<Clock>& o) {
    os << o.m_stats.count();
    return os;
  }

}}

#endif // META_CLOCKS_RECORDER_H
