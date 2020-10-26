
#include <gtest/gtest.h>

#include <meta/filter.h>
#include <meta/remove.h>

namespace tags {
  struct mock {};
}

TEST(unittest, meta_remove) {

  using filtered_list = meta::remove<tags::mock, double, bool, tags::mock, int>::type;
  bool test_result = std::is_same<filtered_list, std::tuple<double, bool, int>>::value;
  ASSERT_EQ(test_result, true);
}

struct foo {};
struct bar {};
struct baz {};

template <typename T>
struct predicate {
  static constexpr bool value = false;
};

template <>
struct predicate<foo> {
  static constexpr bool value = true;
};

template <>
struct predicate<double> {
  static constexpr bool value = true;
};

TEST(unittest, meta_filter) {

  using filtered_list = typename meta::filter<predicate, foo, bar, baz, double, tags::mock>::type;
  bool test_result = std::is_same<filtered_list, std::tuple<foo, double>>::value;
  ASSERT_EQ(test_result, true);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
