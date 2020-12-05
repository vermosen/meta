#pragma once
#ifndef META_CLOCKS_METRICS_AVERAGE_H
#define META_CLOCKS_METRICS_AVERAGE_H

#include <meta/clocks/metric.h>

namespace meta      {
namespace clocks    {

  template <typename Clock>
  class metric<Clock, metrics::type::average> {
  public:
    using duration_t = typename Clock::duration;
  public:
    metric() : m_sum(0), m_count(0) {}
    

    void update(duration_t dur) {
      m_sum += dur;
      m_count++;
    }

    duration_t sample() const {
      return m_sum / m_count;
    }

  private:
    duration_t m_sum;
    std::int64_t m_count;
  };
}}

#endif // META_CLOCKS_METRICS_AVERAGE_H
