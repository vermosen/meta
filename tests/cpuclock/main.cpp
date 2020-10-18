
#include <thread>
#include <chrono>
#include <limits>

#include <gtest/gtest.h>

#include <meta/cpuclock.h>

TEST(top, run) {

  using duration_t = std::chrono::duration<long, std::ratio<1, 1>>;

  using namespace meta;
  auto start = clock::cpu<clock::position::pre>::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  duration_t diff1 = clock::cpu<clock::position::post>::now() - start;

  start = clock::cpu<clock::position::pre>::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  duration_t diff2 = clock::cpu<clock::position::post>::now() - start;

  auto ratio = (double)diff2.count() / (double)diff1.count();

  #ifndef NDEBUG
  EXPECT_NEAR(ratio, 2.0, 1e-1); // TODO: inspect cpu stats at runtime
  #else
  EXPECT_EQ(!(ratio==ratio), true); // in release, computation should return NaN
  #endif
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
