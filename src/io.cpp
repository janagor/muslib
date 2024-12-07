#include "io.hpp"
#include <array>
#include <iostream>

namespace muslib::io {

Signal1 load(const std::string &file_name) {
  const size_t BUFFER_LEN = 4096;
  SNDFILE *infile;
  SF_INFO sfinfo;
  std::array<double, BUFFER_LEN> buffer;
  Signal1 result;
  memset(&sfinfo, 0, sizeof(sfinfo));

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

  int readcount;
  while ((readcount = static_cast<int>(
              sf_read_double(infile, buffer.data(), BUFFER_LEN))) > 0)
    result.insert(result.end(), buffer.data(), buffer.data() + readcount);

  sf_close(infile);
  for (const auto &val : result)
    std::cout << val << ", ";
  std::cout << std::endl;
  return result;
}

Signal1 resample(const Signal1 &original, int from_srate, int to_srate,
                 int num_channels) {
  if (from_srate == to_srate) {
    return original;
  }

  int from_nframes = static_cast<int>(original.size());
  int to_nframes = static_cast<int>(original.size() *
                                    static_cast<double>(to_srate) / from_srate);
  Signal1 resampled_data(to_nframes * num_channels);

  for (int ch = 0; ch < num_channels; ++ch) {
    for (int i = 0; i < to_nframes; ++i) {
      double src_pos = static_cast<double>(i) * from_srate / to_srate;
      int int_pos = static_cast<int>(src_pos);
      double frac = src_pos - int_pos;

      if (int_pos + 1 < from_nframes) {
        resampled_data[i * num_channels + ch] =
            (1.0 - frac) * original[int_pos * num_channels + ch] +
            frac * original[(int_pos + 1) * num_channels + ch];
      } else {
        resampled_data[i * num_channels + ch] =
            original[int_pos * num_channels + ch];
      }
    }
  }
  return resampled_data;
}

} // namespace muslib::io
