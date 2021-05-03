#pragma once
#ifndef META_BUNDLES_SOA_H
#define META_BUNDLES_SOA_H

#include <vector>
#include <memory>

#include <meta/bundle.h>

#include <meta/bundles/containers/soa.h>

namespace meta {

  template <
    typename T
  >
  class bundle<T, bundles::layout::soa, std::vector<T, std::allocator<T>>> {
  public:

    void push_back(T value) {

    }
  };
}

#endif // META_BUNDLES_SOA_H
