#include <vector>
#include <type_traits>

#include <gtest/gtest.h>

#include <boost/pfr.hpp>

#include "mystruct.h"

TEST(unittest, bundle_dereference) {

  dummy::mystruct s = {10, "bar", true};
  auto t = boost::pfr::get<0>(s);
  EXPECT_EQ(t, 10);
}

TEST(unittest, bundle_getsize) {

  dummy::mystruct s = {10, "bar", true};
  constexpr std::size_t t = boost::pfr::detail::fields_count<decltype(s)>();
  EXPECT_EQ(t, 3);
}

TEST(unittest, bundle_gettype) {

  dummy::mystruct s = {10, "bar", true};
  static_assert(std::is_same<decltype(boost::pfr::get<0>(s)), int&>::value, "type mismatch");

  using deref_t = std::remove_reference<decltype(boost::pfr::get<0>(s))>::type;
  static_assert(std::is_same<deref_t, int>::value, "type mismatch");
}

TEST(unittest, bundle_gettype2) {

  // only with the type
  using ref_t = decltype(boost::pfr::get<0>(std::declval<dummy::mystruct>()));
  using obj_t = std::remove_reference<ref_t>::type;
  static_assert(std::is_same<obj_t, int>::value, "type mismatch");
}

#include <meta/bundles/aos.h>

TEST(unittest, bundle_aos) {

  using bundle_t = meta::bundle<dummy::mystruct, meta::bundles::layout::aos>;
  
  bundle_t b;
  b.push_back({10, "bar", true});
}

#include <meta/bundles/soa.h>
TEST(unittest, bundle_soa) {

  using bundle_t = meta::bundle<dummy::mystruct, meta::bundles::layout::soa>;
  
  bundle_t b;
  b.push_back({10, "bar", true});
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
