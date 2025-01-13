#include <gtest/gtest.h>

#include "common.hpp"
#include "transform.hpp"
using namespace muslib;
using namespace muslib::transform;

TEST(TestDiff, BasicTest) {
  Signal1 input = {1.0, 2.0, 3.0, 4.0};
  Signal1 expected = {1.0, 1.0, 1.0};

  Signal1 result = _diff(input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(TestDiff, EmptyInput) {
  Signal1 input = {};
  Signal1 result = _diff(input);

  ASSERT_TRUE(result.empty());
}

TEST(TestDiff, SingleElement) {
  Signal1 input = {5.0};
  Signal1 result = _diff(input);

  ASSERT_TRUE(result.empty());
}

TEST(TestDiff, NegativeNumbers) {
  Signal1 input = {-1.0, -2.0, -3.0};
  Signal1 expected = {-1.0, -1.0};

  Signal1 result = _diff(input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(TestDiff, FloatingPointNumbers) {
  Signal1 input = {1.1, 2.2, 3.3, 4.4};
  Signal1 expected = {1.1, 1.1, 1.1};

  Signal1 result = _diff(input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}
///////////////////////////////////////////////////////////////////////////////
TEST(TestLinspace, SinglePoint) {
  Signal1 result = _linspace(0.0, 10.0, 1);
  Signal1 expected = {0.0};

  ASSERT_EQ(result.size(), expected.size());
  ASSERT_DOUBLE_EQ(result[0], expected[0]);
}

TEST(TestLinspace, TwoPoints) {
  Signal1 result = _linspace(0.0, 10.0, 2);
  Signal1 expected = {0.0, 10.0};

  ASSERT_EQ(result.size(), expected.size());
  ASSERT_DOUBLE_EQ(result[0], expected[0]);
  ASSERT_DOUBLE_EQ(result[1], expected[1]);
}

TEST(TestLinspace, FivePoints) {
  Signal1 result = _linspace(0.0, 10.0, 5);
  Signal1 expected = {0.0, 2.5, 5.0, 7.5, 10.0};

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(TestLinspace, NegativeRange) {
  Signal1 result = _linspace(-10.0, -2.0, 3);
  Signal1 expected = {-10.0, -6.0, -2.0};

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(TestLinspace, SameMinMax) {
  Signal1 result = _linspace(5.0, 5.0, 5);
  Signal1 expected = {5.0, 5.0, 5.0, 5.0, 5.0};

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(TestLinspace, MinGreaterThanMax) {
  Signal1 result = _linspace(10.0, 0.0, 5);
  Signal1 expected = {10.0, 7.5, 5.0, 2.5, 0.0};

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}
///////////////////////////////////////////////////////////////////////////////
TEST(MaximumTest, AllValuesGreaterThanLHS) {
  Signal1 input = {10.0, 20.0, 30.0};
  double lhs = 5.0;
  Signal1 expected = {10.0, 20.0, 30.0};

  Signal1 result = _maximum(lhs, input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MaximumTest, AllValuesSmallerThanLHS) {
  Signal1 input = {1.0, 2.0, 3.0};
  double lhs = 5.0;
  Signal1 expected = {5.0, 5.0, 5.0};

  Signal1 result = _maximum(lhs, input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MaximumTest, SomeValuesEqualToLHS) {
  Signal1 input = {3.0, 5.0, 7.0};
  double lhs = 5.0;
  Signal1 expected = {5.0, 5.0, 7.0};

  Signal1 result = _maximum(lhs, input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MaximumTest, EmptyVector) {
  Signal1 input = {};
  double lhs = 5.0;
  Signal1 result = _maximum(lhs, input);

  ASSERT_TRUE(result.empty());
}

TEST(MaximumTest, SingleElement) {
  Signal1 input = {3.0};
  double lhs = 5.0;
  Signal1 expected = {5.0};

  Signal1 result = _maximum(lhs, input);

  ASSERT_EQ(result.size(), expected.size());
  ASSERT_DOUBLE_EQ(result[0], expected[0]);
}

TEST(MaximumTest, MixedValues) {
  Signal1 input = {1.0, 10.0, 0.0, 5.0};
  double lhs = 3.0;
  Signal1 expected = {3.0, 10.0, 3.0, 5.0};

  Signal1 result = _maximum(lhs, input);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}
///////////////////////////////////////////////////////////////////////////////
TEST(MinimumTest, IdenticalVectors) {
  Signal1 lhs = {1.0, 2.0, 3.0};
  Signal1 rhs = {1.0, 2.0, 3.0};
  Signal1 expected = {1.0, 2.0, 3.0};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MinimumTest, DifferentSizes) {
  Signal1 lhs = {1.0, 2.0, 3.0};
  Signal1 rhs = {1.0, 2.0};

  ASSERT_THROW(_minimum(lhs, rhs), std::runtime_error);
}

TEST(MinimumTest, LhsGreaterThanRhs) {
  Signal1 lhs = {5.0, 6.0, 7.0};
  Signal1 rhs = {1.0, 2.0, 3.0};
  Signal1 expected = {1.0, 2.0, 3.0};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MinimumTest, RhsGreaterThanLhs) {
  Signal1 lhs = {1.0, 2.0, 3.0};
  Signal1 rhs = {5.0, 6.0, 7.0};
  Signal1 expected = {1.0, 2.0, 3.0};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MinimumTest, MixedValues) {
  Signal1 lhs = {3.0, 5.0, 1.0};
  Signal1 rhs = {4.0, 2.0, 6.0};
  Signal1 expected = {3.0, 2.0, 1.0};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_DOUBLE_EQ(result[i], expected[i]);
  }
}

TEST(MinimumTest, EmptyVectors) {
  Signal1 lhs = {};
  Signal1 rhs = {};
  Signal1 expected = {};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
}

TEST(MinimumTest, SingleElement) {
  Signal1 lhs = {5.0};
  Signal1 rhs = {3.0};
  Signal1 expected = {3.0};

  Signal1 result = _minimum(lhs, rhs);

  ASSERT_EQ(result.size(), expected.size());
  ASSERT_DOUBLE_EQ(result[0], expected[0]);
}
