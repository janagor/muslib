#include <gtest/gtest.h>

#include "io.hpp"

TEST(TestLoad, OneValue) {
  std::cout << "sine" << std::endl;
  muslib::io::load("/home/janagorski/studia/2024Z/ZPR/projekt/muslib/"
                   "data_examples/sine.wav");
  std::cout << "trumpet" << std::endl;
  muslib::io::load("/home/janagorski/studia/2024Z/ZPR/projekt/muslib/"
                   "data_examples/trumpet.wav");

  EXPECT_EQ(0, 0);
}
