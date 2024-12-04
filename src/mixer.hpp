#include <vector>
#include <numeric>

namespace muslib::mixer {

using Signal = std::vector<double>;
using Signal2d = std::vector<std::vector<double>>;

// TODO: to be implemented
// Signal sin(double duration, unsigned sample_rate, double freq);
// Signal cos(double duration, unsigned sample_rate, double freq);
// Signal zero_crossing_rate(const Signal& sig);
// Signal zero_crossings(const Signal& sig);

double avg(const Signal& sig);
double variance(const Signal& sig);
double std_dev(const Signal& sig);

Signal2d frame(const Signal& sig, unsigned frame_length, unsigned hop_length);
Signal normalized(const Signal& sig);

}
