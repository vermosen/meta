#pragma once
#ifndef META_CLOCKS_METRICS_STDDEV_H
#define META_CLOCKS_METRICS_STDDEV_H

#include <cmath>
#include <array>

#include <meta/clocks/metric.h>

namespace meta   {
namespace clocks {

  /*!
   * Terriberry, Timothy B. (2007), Computing Higher-Order Moments Online
   * https://people.xiph.org/~tterribe/notes/homs.html 
   */
  template <typename Clock>
  class metric<Clock, metrics::type::stddev> {
  public:
    using duration_t = typename Clock::duration;
  public:
    metric() : m_m({0, 0}), m_n(0) {}
    
    void update(duration_t dur) {
      
      std::size_t n = m_n; m_n++;
      double delta = dur.count() - m_m[0];
      double delta_n = delta / m_n;
      double term = delta * delta_n * n;

      m_m[1] += term;
      m_m[0] += delta_n;
    }

    duration_t collect() const { 
      auto res = m_m;
      res[1] = std::sqrt(res[1]) / (m_n - 1);               // stddev
      auto rep = typename duration_t::rep(res[1]);
      return duration_t(rep);
    }

  private:
    std::array<double, 2> m_m;                              // average, stddev
    std::size_t m_n;
  };
}}

#endif // META_CLOCKS_METRICS_STDDEV_H
