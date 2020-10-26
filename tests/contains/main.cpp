
#include <gtest/gtest.h>

#include <meta/contains.h>

namespace tags {
  struct mock {};
}

template <typename ... Args>
struct test {
  static constexpr bool value = meta::contains<tags::mock, Args...>::value;
};

TEST(unittest, meta_contains_proto) {

  using test_type1 = test<double, tags::mock, bool>;
  using test_type2 = test<tags::mock, tags::mock, bool>;
  using test_type3 = test<double, int, bool>;
  using test_type4 = test<void>;

  ASSERT_EQ(test_type1::value, true);
  ASSERT_EQ(test_type2::value, true);
  ASSERT_EQ(test_type3::value, false);
  ASSERT_EQ(test_type4::value, false);
}

namespace details {
  template <bool Test, typename ... Args>
  struct test_impl;

  template <typename ... Args>
  struct test_impl<true, Args...> {
    static constexpr bool value = true;
  };

  template <typename ... Args>
  struct test_impl<false, Args...> {
    static constexpr bool value = false;
  };
}

template <typename ... Args>
struct test2 : public details::test_impl<meta::contains<tags::mock, Args...>::value, Args ...> {};

TEST(unittest, meta_contains) {

  static_assert(test2<double, tags::mock, bool>::value, "error!");
  static_assert(!test2<double, int, bool>::value, "error!");
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
