#pragma once
#ifndef META_CLOCKS_METRICS_KURTOSIS_H
#define META_CLOCKS_METRICS_KURTOSIS_H

#include <cmath>

#include <meta/clocks/metric.h>

namespace meta   {
namespace clocks {

  /*!
   * Terriberry, Timothy B. (2007), Computing Higher-Order Moments Online
   * https://people.xiph.org/~tterribe/notes/homs.html 
   */
  template <typename Clock>
  class metric<Clock, metrics::type::kurtosis> {
  public:
    using duration_t = typename Clock::duration;
  public:
    metric() : m_m({0, 0, 0, 0}), m_n(0) {}
    
    void update(duration_t dur) {
      
      auto n = m_n; m_n++;
      auto delta = dur.count() - m_m[0];
      auto delta_n = delta / m_n;
      auto delta_n2 = delta_n * delta_n;
      auto term = delta * delta_n * n;

      m_m[3] += term * delta_n2 * (m_n * m_n - 3 * m_n + 3)
        + 6 * delta_n2 * m_m[1] - 4 * delta_n * m_m[2];
      m_m[2] += term * delta_n * (m_n - 2) - 3 * delta_n * m_m[1];
      m_m[1] += term;
      m_m[0] = m_m[0] + delta_n;
    }

    duration_t collect() const { 
    auto res = m_m;
    res[3] = m_n * (res[3] / (res[1] * res[1])) - 3;  // excess kurtosis
    res[2] *= std::sqrt(m_n / res[1]) / res[1];       // skewness
    res[1] = std::sqrt(res[1]) / (m_n - 1);           // variance
    auto rep = typename duration_t::rep(res[3]);
    return duration_t(rep);
    }

  private:
    std::array<double, 4> m_m;                              // average, stddev
    std::size_t m_n;
  };
}}

#endif // META_CLOCKS_METRICS_KURTOSIS_H
