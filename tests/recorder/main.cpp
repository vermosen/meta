
#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <meta/clocks/metrics/all.h>
#include <meta/clocks/recorder.h>

TEST(unittest, meta_recorder_measure) {
  
  using namespace std::literals::chrono_literals;
  using namespace meta::clocks;
  using recorder_t = meta::clocks::recorder<std::chrono::system_clock, metrics::type::average>;
  recorder_t rec;
  
  auto tp = std::chrono::system_clock::now();
  std::this_thread::sleep_for(10ms);
  rec.push(std::chrono::system_clock::now() - tp); 
  // purposedly fails to compile
  // auto& t3 = c.template get<mystruct<myenum::bar>>();
  // ASSERT_EQ(t2.value(), -1);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
