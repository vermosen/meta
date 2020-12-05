#pragma once
#ifndef META_CLOCKS_METRICS_H
#define META_CLOCKS_METRICS_H

namespace meta    {
namespace clocks  {

namespace metrics {
  enum class type {
      sum      = 1
    , average  = 2
    , stddev   = 3
    //, skewness = 4
    //, kurtosis = 5
    //, fractile = 6 -> will require parametrized ctor
  };
}

  template <typename Clock, metrics::type>
  class metric;
}}

#endif // META_CLOCKS_METRICS_H
