
#include <gtest/gtest.h>

#include <string>

#include <meta/detect.h>

template<typename T, typename ... Args>
using has_apply =
decltype(std::declval<T&>().apply(std::declval<Args>()...));

struct foo {};
struct bar {};
struct baz {};

struct client {
  void apply(foo) { m_ctr++; }
  void apply(bar) { m_ctr++; }
  //void apply(baz) { m_ctr++; } // no baz method
  int m_ctr = 0;
};

TEST(unittest, meta_detect_run) {
  static_assert(meta::has_method<has_apply, void, client, foo>::type{});
  static_assert(meta::has_method<has_apply, void, client, bar>::type{});
  //static_assert(meta::has_method<has_apply, void, client, baz>::type{}); // would fail to compile
}

// a dispatching class
template <typename ... Args>
struct dispatch;

template <typename First, typename ... Rest>
struct dispatch<First, Rest ...> {
  static void apply(client& cl) {
    if constexpr (typename meta::has_method<has_apply, void, client, First>::type{}) {
      cl.apply(First());
    }

    dispatch<Rest...>::apply(cl);
  }
};

template <typename First>
struct dispatch<First> {
  static void apply(client& cl) {
    if constexpr (typename meta::has_method<has_apply, void, client, First>::type{}) {
      cl.apply(First());
    }
  }
};


TEST(unittest, meta_detect_unroll) {

  client cl;
  dispatch<foo, bar, baz>::apply(cl); // will only invoke apply(foo) and apply(bar)
  ASSERT_EQ(cl.m_ctr, 2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
