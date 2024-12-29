#include <gtest/gtest.h>

#include "io.hpp"
#include "transform.hpp"

TEST(TestLoad, OneValue) {
  std::cout << "sine" << std::endl;
  muslib::io::load("/home/janagorski/studia/2024Z/ZPR/projekt/muslib/"
                   "data_examples/sine.wav");
  std::cout << "trumpet" << std::endl;
  auto a = muslib::io::load("/home/janagorski/studia/2024Z/ZPR/projekt/muslib/"
                            "data_examples/trumpet.wav");
  auto S = muslib::transform::melspectrogram(a, 22050);
  std::cout << S.size() << std::endl;
  std::cout << S.at(0).size() << std::endl;

  EXPECT_EQ(0, 0);
}
