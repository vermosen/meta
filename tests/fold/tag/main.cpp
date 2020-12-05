#include <tuple>

#include <gtest/gtest.h>

#include <meta/patterns/fold.h>

namespace tags {

  struct foo {};
  struct bar {};
  struct baz {};
}

template <typename Tag>
struct element;

template <>
struct element<tags::foo> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<0>(check) = true; }
};

template <>
struct element<tags::bar> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<1>(check) = true; }
};

template <>
struct element<tags::baz> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<2>(check) = true; }
};

/* template <template <auto> typename T, auto ... Args> 
struct mapper {

  void apply_all(std::tuple<bool, bool, bool>& check) {
    (m_fold.template get<Args>().apply(check), ...);
  }

  meta::fold_tags<T, Args...> m_fold;
}; */

TEST(unittest, meta_fold_tags) {
  // TODO
/*   using mapper_t = mapper<element, tags::foo, tags::bar>;
  mapper_t map;
  std::tuple<bool, bool, bool> checks = { false, false, false };
  map.apply_all(checks);
  ASSERT_EQ(std::get<0>(checks), true);
  ASSERT_EQ(std::get<1>(checks), true);
  ASSERT_EQ(std::get<2>(checks), false); */
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
