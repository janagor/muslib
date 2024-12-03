#include <convert.hpp>
#include <string>
#include <sndfile.h>

namespace muslib:convert {
    void convert_to_format(onst std::string& input_file, const std::string& output_file, const std::string& format){
        SF_INFO sfinfo_in, sfinfo_out;
        SNDFILE *infile, *outfile;

        if(!(infile = sf_open(input_file.c_str(), SFM_READ, &sfinfo_in))){
            std::cerr << "Conversion error, cannot open input file :" << input_file << std::endl;
            return -1;
        }

        sfinfo_out = sfinfo_in;
        sfinfo_out.format = SF_FORMAR_WAV | SF_FORMAR_PCM_16

        if(!(outfile = sf_open(input_file.c_str(), SFM_WRITE, &sfinfo_out))){
            std::cerr << "Conversion error, cannot open output file :" << output_file << std::endl;
            return -2;
        }

        short *buffer = new short[sfinfo_in.frames];

        while(sf_readf_short(infile, buffer, sfinfo_in.frames) > 0){
            sf_writef_short(outfile, buffer, sfinfo_out.frames);
        }

        sfclose(infile);
        sfclose(outfile);

        delete[] buffer;
    }
}