#include "mixer.hpp"
#include <gtest/gtest.h>

// helper functions
void compare_signal(muslib::Signal1 expected, muslib::Signal1 received) {
  ASSERT_EQ(expected.size(), received.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_DOUBLE_EQ(expected[i], received[i]);
  }
}

void compare_signal2d(muslib::Signal2 expected, muslib::Signal2 received) {
  ASSERT_EQ(expected.size(), received.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    compare_signal(expected[i], received[i]);
  }
}

TEST(Average, OneValue) {
  muslib::Signal1 input{1.0, 1.0};

  EXPECT_DOUBLE_EQ(muslib::mixer::avg(input), 1.0);
}

TEST(Frame, OneValue) {
  muslib::Signal2 expected{
      {1.0},
  };
  muslib::Signal1 input{1.0};
  muslib::Signal2 received = muslib::mixer::frame(input, 1, 1);
  compare_signal2d(expected, received);
}
