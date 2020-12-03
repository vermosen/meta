
#include <thread>
#include <chrono>
#include <limits>

#include <gtest/gtest.h>

#include <meta/clocks/cpu.h>
#include <meta/clocks/recorder.h>

TEST(unittest, cpu_clock) {

  using duration_t = std::chrono::duration<long, std::ratio<1, 1>>;

  using namespace meta;
  auto start = clocks::cpu<clocks::position::pre>::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  duration_t diff1 = clocks::cpu<clocks::position::post>::now() - start;

  start = clocks::cpu<clocks::position::pre>::now();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  duration_t diff2 = clocks::cpu<clocks::position::post>::now() - start;

  auto ratio = (double)diff2.count() / (double)diff1.count();

  #ifndef NDEBUG
  EXPECT_NEAR(ratio, 2.0, 1e-1);
  // TODO: get cpu frequency at runtime
  //EXPECT_NEAR(diff1.count(), 2.0, 1e-1); // TODO: inspect cpu stats at runtime
  //EXPECT_NEAR(diff2.count(), 2.0, 1e-1); // TODO: inspect cpu stats at runtime
  #else
  EXPECT_EQ(!(ratio==ratio), true); // in release, computation should return NaN
  #endif
}

TEST(unittest, clock_add_duration) {

  using namespace meta;

  using duration_t = std::chrono::duration<long, std::ratio<1, 1>>;

  duration_t total(0);

  for (int i = 0; i < 10; i ++) {
    auto start = clocks::cpu<clocks::position::pre>::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto diff = clocks::cpu<clocks::position::post>::now() - start;
    total += diff;
  }

  #ifndef NDEBUG
  EXPECT_NE(total.count(), 0.0); // should be ~ computer frequency / 100
  #else
  EXPECT_EQ(total.count(), 0.0);
  #endif
}

TEST(unittest, clock_collect_stats) {

  using namespace meta;
  using clock_type = std::chrono::system_clock;
  using recorder_t = meta::clocks::recorder<clock_type>;
  using duration_t = typename clock_type::duration;

  recorder_t rec;
  duration_t total(0);

  for (int i = 0; i < 10; i ++) {
    auto start = clock_type::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto diff = clock_type::now() - start;
    rec.add(diff);
  }

  std::stringstream ss; ss
    << rec << std::endl;

  auto res = ss.str();

  EXPECT_EQ(0.0, 0.0); // should be ~ computer frequency / 100
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
