#include "io.hpp"
#include <array>
#include <iostream>

namespace muslib::io {

std::vector<double> load(const std::string &file_name) {
  const int samplerate = 22050; // TODO: make it a variable param
  const size_t BUFFER_LEN = 4096;
  SNDFILE *infile;
  SF_INFO sfinfo;
  std::array<double, BUFFER_LEN> buffer;
  std::vector<double> result;

  memset(&sfinfo, 0, sizeof(sfinfo));
  sfinfo.samplerate = samplerate;

  if (!(infile = sf_open(file_name.c_str(), SFM_READ, &sfinfo))) {
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
} // namespace muslib::io
