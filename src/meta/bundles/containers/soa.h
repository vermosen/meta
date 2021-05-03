#pragma once
#ifndef META_BUNDLES_CONTAINERS_SOA_H
#define META_BUNDLES_CONTAINERS_SOA_H

#include <vector>
#include <memory>
#include <type_traits>

#include <boost/pfr/core.hpp>

#include <meta/bundles/layout.h>
#include <meta/bundles/container.h>

namespace meta::bundles {

namespace details {
  
  template <std::size_t I, typename T, typename Container>
  struct container : public container<I - 1, T, Container> {
    using ref_t = decltype(boost::pfr::get<0>(std::declval<T>()));
    using obj_t = typename std::remove_reference<ref_t>::type;
  };

  template <typename T, typename Container>
  struct container<0, T, Container> {
    using ref_t = decltype(boost::pfr::get<0>(std::declval<T>()));
    using obj_t = typename std::remove_reference<ref_t>::type;
  };
}

  template <
    typename T
  >
  class container<T, bundles::layout::soa, std::vector<T, std::allocator<T>>> {
  public:

  //private:
  //  std::tuple<int, long> m_impl;
  };
}

#endif // META_BUNDLES_CONTAINERS_SOA_H
