#include "mixer.hpp"
#include <gtest/gtest.h>

// helper functions
void compare_signal(muslib::mixer::Signal expected,
                    muslib::mixer::Signal received) {
  ASSERT_EQ(expected.size(), received.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(expected[i], received[i]);
  }
}

void compare_signal2d(muslib::mixer::Signal2d expected,
                      muslib::mixer::Signal2d received) {
  ASSERT_EQ(expected.size(), received.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    compare_signal(expected[i], received[i]);
  }
}

TEST(Average, OneValue) {
  muslib::mixer::Signal input{1.0, 1.0};

  EXPECT_DOUBLE_EQ(muslib::mixer::avg(input), 1.0);
}

TEST(Frame, OneValue) {
  muslib::mixer::Signal2d expected{
      {1.0},
  };
  muslib::mixer::Signal input{1.0};
  muslib::mixer::Signal2d received = muslib::mixer::frame(input, 1, 1);
  compare_signal2d(expected, received);
}
