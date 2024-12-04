#include "common.hpp"

namespace muslib::mixer {

// TODO: to be implemented
// Signal1 sin(double duration, unsigned sample_rate, double freq);
// Signal1 cos(double duration, unsigned sample_rate, double freq);
// Signal1 zero_crossing_rate(const Signal& sig);
// Signal1 zero_crossings(const Signal& sig);

double avg(const Signal1 &sig);
double variance(const Signal1 &sig);
double std_dev(const Signal1 &sig);

Signal2 frame(const Signal1 &sig, unsigned frame_length, unsigned hop_length);
Signal1 normalized(const Signal1 &sig);

} // namespace muslib::mixer
