#pragma once
#ifndef META_BUNDLE_H
#define META_BUNDLE_H

#include <vector>

#include <meta/bundles/layout.h>

namespace meta {

  template <
      typename T
    , bundles::layout Layout
    , typename Container = std::vector<T, std::allocator<T>>
  >
  class bundle;
}

#endif // META_BUNDLE_H
