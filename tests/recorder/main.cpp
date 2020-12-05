
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <meta/clocks/metrics/all.h>
#include <meta/clocks/recorder.h>
#include <meta/clocks/cpu.h>

TEST(unittest, meta_recorder_measure) {
  
  using namespace std::literals::chrono_literals;
  using namespace meta::clocks;
  using recorder_t = recorder<std::chrono::system_clock, metrics::type::sum>;
  recorder_t rec;
  
  for (int i = 0; i < 10; i++) {
    auto tp = std::chrono::system_clock::now();
    std::this_thread::sleep_for(10ms);
    rec.push(std::chrono::system_clock::now() - tp); 
  }

  auto total = rec.sample<metrics::type::sum>();
  ASSERT_GE(total, 100ms);
}

TEST(unittest, meta_recorder_measure_cpuclock) {
  
  using namespace meta::clocks;
  using namespace std::literals::chrono_literals;
  using recorder_t = recorder<cpu<>, metrics::type::average, metrics::type::sum>;
  recorder_t rec;
  
  for (int i = 0; i < 10; i++) {
    auto tp = cpu<position::pre>::now();
    std::this_thread::sleep_for(1ms);
    rec.push(cpu<position::post>::now() - tp); 
  }

  auto total = rec.sample<metrics::type::sum>();
  auto average = rec.sample<metrics::type::average>();
  ASSERT_NEAR(total.count(), 10 * average.count(), 10);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
