#pragma once
#ifndef META_BUNDLES_CONTAINER_H
#define META_BUNDLES_CONTAINER_H

#include <meta/bundles/layout.h>

namespace meta::bundles {

  template <
      typename T
    , bundles::layout Layout
    , typename Container
  >
  class container;
}

#endif // META_BUNDLES_CONTAINER_H
