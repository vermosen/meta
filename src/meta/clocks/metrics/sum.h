#pragma once
#ifndef META_CLOCKS_METRICS_SUM_H
#define META_CLOCKS_METRICS_SUM_H

#include <meta/clocks/metric.h>

namespace meta      {
namespace clocks    {

  template <typename Clock>
  class metric<Clock, metrics::type::sum> {
  public:
    using duration_t = typename Clock::duration;
  
  public:
    void update(duration_t dur) {
      m_sum += dur;
    }

    void sample() const {
      return m_sum;
    }

  private:
    duration_t m_sum;
  };
}}

#endif // META_CLOCKS_METRICS_SUM_H
