#include <tuple>

#include <gtest/gtest.h>

#include <meta/patterns/fold.h>

// example 1: works with enum class
enum class type {foo, bar, baz};

template <type T>
struct element;

template <>
struct element<type::foo> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<0>(check) = true; }
};

template <>
struct element<type::bar> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<1>(check) = true; }
};

template <>
struct element<type::baz> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<2>(check) = true; }
};

template <template <auto> typename T, auto ... Args> 
struct mapper {

  void apply_all(std::tuple<bool, bool, bool>& check) {
    (m_fold.template get<Args>().apply(check), ...);
  }

  meta::fold_enum<T, Args...> m_fold;
};

TEST(unittest, meta_fold_enum_class) {
  using mapper_t = mapper<element, type::foo, type::bar>;
  mapper_t map;
  std::tuple<bool, bool, bool> checks = { false, false, false };
  map.apply_all(checks);
  ASSERT_EQ(std::get<0>(checks), true);
  ASSERT_EQ(std::get<1>(checks), true);
  ASSERT_EQ(std::get<2>(checks), false);
}

template <typename Arg, type T>
struct element_ext;

template <typename Arg>
struct element_ext<Arg, type::foo> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<0>(check) = true; }
};

template <typename Arg>
struct element_ext<Arg, type::bar> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<1>(check) = true; }
};

template <typename Arg>
struct element_ext<Arg, type::baz> {
  void apply(std::tuple<bool, bool, bool>& check) { std::get<2>(check) = true; }
};

struct arg {};

template <type Type>
using alias_t = element_ext<arg, Type>;

TEST(unittest, meta_fold_enum_alias) {

  using mapper_t = mapper<alias_t, type::foo, type::bar>;
  mapper_t map;
  std::tuple<bool, bool, bool> checks = { false, false, false };
  map.apply_all(checks);
  ASSERT_EQ(std::get<0>(checks), true);
  ASSERT_EQ(std::get<1>(checks), true);
  ASSERT_EQ(std::get<2>(checks), false);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
