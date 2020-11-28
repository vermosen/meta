
#include <thread>
#include <chrono>
#include <limits>

#include <gtest/gtest.h>

#include <meta/cpuclock.h>

TEST(unittest, cpuclock) {

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
  // TODO: get cpu frequency at runtime
  EXPECT_NE(ratio, 0.0);
  //EXPECT_NEAR(diff1.count(), 2.0, 1e-1); // TODO: inspect cpu stats at runtime
  //EXPECT_NEAR(diff2.count(), 2.0, 1e-1); // TODO: inspect cpu stats at runtime
  #else
  EXPECT_EQ(!(ratio==ratio), true); // in release, computation should return NaN
  #endif
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
