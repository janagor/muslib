#pragma once

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstring>
#include <iostream>
#include <numbers>
#include <numeric>
#include <vector>

namespace muslib {

using Signal1 = std::vector<double>;
using Signal2 = std::vector<std::vector<double>>;
using Signal1Complex = std::vector<std::complex<double>>;
using Signal2Complex = std::vector<std::vector<std::complex<double>>>;
using Time = int;

inline bool is_fast_size(int n) {
  while (n % 2 == 0)
    n /= 2;
  while (n % 3 == 0)
    n /= 3;
  while (n % 5 == 0)
    n /= 5;
  return n == 1;
}

inline int next_fast_len(int n) {
  while (!is_fast_size(n)) {
    n++;
  }
  return n;
}
inline void _abs(Signal1 &s) {
  std::for_each(s.begin(), s.end(), [](double &x) { x = std::abs(x); });
}

inline void _abs2(Signal1 &s) {
  std::for_each(s.begin(), s.end(), [](double &x) { x *= x; });
}

inline Signal1 _abs2(Signal1Complex &s) {
  Signal1 result(s.size());
  for (size_t i = 0; i < s.size(); ++i) {
    result.at(i) = std::abs(s.at(i)) * std::abs(s.at(i));
  }
  return result;
}

inline Signal2 _norm_max(const Signal2 &s) {
  // Signal2 result(s.size(), Signal1(s.at(0).size()));
  Signal2 result(s);
  auto max = std::numeric_limits<double>::min();
  for (size_t i = 0; i < s.size(); ++i)
    for (size_t j = 0; j < s.at(0).size(); ++j)
      if (s.at(i).at(j) > max)
        max = s.at(i).at(j);

  for (size_t i = 0; i < s.size(); ++i)
    for (size_t j = 0; j < s.at(0).size(); ++j)
      result.at(i).at(j) = s.at(i).at(j) / max;

  return result;
}

inline Signal1 _linspace(double min, double max, unsigned n) {
  Signal1 res(n);
  if (n == 1) {
    res.at(0) = min;
    return res;
  }
  auto diff = (max - min) / (n - 1);
  std::iota(res.begin(), res.end(), 0);
  std::for_each(res.begin(), res.end(),
                [&](double &value) { value = min + value * diff; });
  return res;
}

inline void _pad_edge(Signal1 &sig, unsigned begin_size, unsigned end_size) {

  Signal1 padding_lhs(begin_size, sig.at(0));
  Signal1 padding_rhs(end_size, sig.at(sig.size() - 1));

  sig.insert(sig.begin(), padding_lhs.begin(), padding_lhs.end());
  sig.insert(sig.end(), padding_rhs.begin(), padding_rhs.end());
}
inline void _pad_constant(Signal1 &sig, unsigned begin_size,
                          unsigned end_size) {

  Signal1 padding_lhs(begin_size, 0);
  Signal1 padding_rhs(end_size, 0);

  sig.insert(sig.begin(), padding_lhs.begin(), padding_lhs.end());
  sig.insert(sig.end(), padding_rhs.begin(), padding_rhs.end());
}

inline void _pad_linear_ramp(Signal1 &sig, unsigned begin_size,
                             unsigned end_size, double lhs = 0,
                             double rhs = 0) {
  Signal1 padding_lhs(begin_size);
  Signal1 padding_rhs(end_size);
  std::iota(padding_lhs.begin(), padding_lhs.end(), 0);
  std::iota(padding_rhs.begin(), padding_rhs.end(), 1);
  double lrange = sig.at(0) - lhs;
  double rrange = rhs - sig.at(sig.size() - 1);
  double lfactor = lrange / begin_size;
  double rfactor = rrange / end_size;

  for (size_t i = 0; i < begin_size; ++i)
    padding_lhs.at(i) = padding_lhs.at(i) * lfactor + lhs;

  for (size_t i = 0; i < end_size; ++i)
    padding_rhs.at(i) = padding_rhs.at(i) * rfactor + sig.at(sig.size() - 1);

  sig.insert(sig.begin(), padding_lhs.begin(), padding_lhs.end());
  sig.insert(sig.end(), padding_rhs.begin(), padding_rhs.end());
}

} // namespace muslib
