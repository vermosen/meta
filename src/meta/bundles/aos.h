#pragma once
#ifndef META_BUNDLES_AOS_H
#define META_BUNDLES_AOS_H

#include <vector>
#include <memory>

#include <meta/bundle.h>

namespace meta {

  template <
      typename T
  >
  class bundle<T, bundles::layout::aos, std::vector<T, std::allocator<T>>> {
  public:
    void push_back(T value) {
      m_container.push_back(value);
    }
  
  private:
    std::vector<T, std::allocator<T>> m_container;
  };
}

#endif // META_BUNDLES_AOS_H
