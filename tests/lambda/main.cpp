
#include <gtest/gtest.h>

#include <meta/lambda/arguments.h>
#include <meta/lambda/arity.h>
#include <meta/lambda/returns.h>

TEST(unittest, lambda_deduce_arg_type) {

  auto l = [&](int, char) { /* do something with i and c */ };

  static_assert(
    std::is_same<
    typename meta::arguments<decltype(l)>::type
    , std::tuple<int, char>
    >::value, "std::tuple<int, char> is expected"); 
}

TEST(unittest, lambda_deduce_arity) {

  auto l = [&](int, char) { /* do something */ };

  static_assert(
      meta::arity<decltype(l)>::value == 2
    , "std::tuple<int, char> is expected");
}

TEST(unittest, lambda_deduce_return_type) {

  auto l = [&](int, char) -> int { /* do something */; return 1; };

  static_assert(
      std::is_same<typename meta::returns<decltype(l)>::type, int>::value
    , "int expected");
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
