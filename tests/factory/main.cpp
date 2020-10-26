
#include <gtest/gtest.h>

#include <meta/patterns/factory.h>

enum class tickers {
    base      = 0
  , derived_1 = 1
  , derived_2 = 2
};

class base_noargs {
public:
  base_noargs() {}
  virtual ~base_noargs() {}
  virtual tickers get_type() { return tickers::base; }

  DECLARE_REGISTER(base_noargs, tickers, base_noargs);
};

DEFINE_FACTORY(base_noargs, tickers);

class derived_1_noargs : public base_noargs {
public:
  virtual tickers get_type() { return tickers::derived_1; }
  DECLARE_REGISTER(base_noargs, tickers, derived_1_noargs);
};

class derived_2_noargs : public base_noargs {
public:
  virtual tickers get_type() { return tickers::derived_2; }
  DECLARE_REGISTER(base_noargs, tickers, derived_2_noargs);
};

DEFINE_REGISTER(base_noargs, tickers, tickers::base, base_noargs);
DEFINE_REGISTER(base_noargs, tickers, tickers::derived_1, derived_1_noargs);
DEFINE_REGISTER(base_noargs, tickers, tickers::derived_2, derived_2_noargs);

TEST(unittest, meta_factory_noargs) {

  auto p1 = meta::factory<base_noargs, tickers>::create_instance(tickers::base);
  auto p2 = meta::factory<base_noargs, tickers>::create_instance(tickers::derived_1);
  auto p3 = meta::factory<base_noargs, tickers>::create_instance(tickers::derived_2);

  ASSERT_EQ(p1->get_type(), tickers::base) << "incorrect class type factored";
  ASSERT_EQ(p2->get_type(), tickers::derived_1) << "incorrect class type factored";
  ASSERT_EQ(p3->get_type(), tickers::derived_2) << "incorrect class type factored";
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
