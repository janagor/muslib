#include "convert.hpp"
#include <sndfile.h>
#include <string>

namespace muslib::convert {
int convert_to_format(const std::string &input_file,
                      const std::string &output_file) {
  SF_INFO sfinfo_in, sfinfo_out;
  SNDFILE *infile, *outfile;

  if (!(infile = sf_open(input_file.c_str(), SFM_READ, &sfinfo_in))) {
    std::cerr << "Conversion error, cannot open input file :" << input_file
              << std::endl;
    return -1;
  }

  sfinfo_out = sfinfo_in;
  sfinfo_out.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

  if (!(outfile = sf_open(input_file.c_str(), SFM_WRITE, &sfinfo_out))) {
    std::cerr << "Conversion error, cannot open output file :" << output_file
              << std::endl;
    return -2;
  }

  short *buffer = new short[sfinfo_in.frames];

  while (sf_readf_short(infile, buffer, sfinfo_in.frames) > 0) {
    sf_writef_short(outfile, buffer, sfinfo_out.frames);
  }

  sf_close(infile);
  sf_close(outfile);

  delete[] buffer;
  return 0;
}
} // namespace muslib::convert
