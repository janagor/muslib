#include "io.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <ranges>

namespace muslib::io {

Signal1 to_mono(const Signal1 &input, int chnum) {
  if (chnum < 1)
    throw std::runtime_error("wrong chnum");
  if (chnum == 1)
    return input;
  Signal1 result;
  for (auto chunk : input | std::ranges::views::chunk(chnum)) {
    double sum = std::accumulate(chunk.begin(), chunk.end(), 0.0);
    double avg = sum / chunk.size();
    result.emplace_back(avg);
  }

  return result;
}

Signal1 load(const std::string &file_name) {
  SNDFILE *infile;
  SF_INFO sfinfo;

  infile = sf_open(file_name.c_str(), SFM_READ, &sfinfo);
  if (!infile) {
    std::cout << "Error : could not open file : " << file_name << std::endl;
    puts(sf_strerror(NULL));
    exit(1);
  }

  if (!sf_format_check(&sfinfo)) {
    sf_close(infile);
    printf("Invalid encoding\n");
    exit(1);
  };

  Signal1 result(sfinfo.frames * sfinfo.channels);
  sf_read_double(infile, result.data(), sfinfo.frames * sfinfo.channels);

  sf_close(infile);

  return to_mono(result, sfinfo.channels);
}

Signal1 resample(const Signal1 &original, int from_srate, int to_srate) {
  if (from_srate == to_srate) {
    return original;
  }

  int from_nframes = static_cast<int>(original.size());
  int to_nframes = static_cast<int>(
      std::ceil(from_nframes * (static_cast<double>(to_srate) / from_srate)));

  Signal1 resampled_data(to_nframes);

  for (int i = 0; i < to_nframes; ++i) {
    double src_pos = static_cast<double>(i) * from_srate / to_srate;
    int int_pos = static_cast<int>(src_pos);
    double frac = src_pos - int_pos;

    if (int_pos + 1 < from_nframes) {
      resampled_data[i] =
          (1.0 - frac) * original[int_pos] + frac * original[int_pos + 1];
    } else {
      resampled_data[i] = original[int_pos];
    }
  }

  return resampled_data;
}

} // namespace muslib::io
