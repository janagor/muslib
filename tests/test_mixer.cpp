#include "mixer.hpp"
#include <gtest/gtest.h>

using namespace muslib::mixer;

// helper functions
void compare_signal(Signal expected, Signal received) {
    ASSERT_EQ(expected.size(), received.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_DOUBLE_EQ(expected[i], received[i]);
    }
}

void compare_signal2d(Signal2d expected, Signal2d received) {
    ASSERT_EQ(expected.size(), received.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        compare_signal(expected[i], received[i]);
    }
}

TEST(Average, OneValue) {
    Signal input{1.0, 1.0};

    EXPECT_DOUBLE_EQ(avg(input), 1.0);
}

TEST(Frame, OneValue) {
    Signal2d expected {
        {1.0},
    };
    Signal input{1.0};
    Signal2d received = frame(input, 1, 1);
    compare_signal2d(expected, received);
}
