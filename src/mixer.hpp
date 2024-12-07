#include "common.hpp"

namespace muslib::mixer {

// TODO: to be implemented
// Signal1 sin(double duration, unsigned sample_rate, double freq);
// Signal1 cos(double duration, unsigned sample_rate, double freq);
// Signal1 zero_crossing_rate(const Signal& sig);
// Signal1 zero_crossings(const Signal& sig);

/**
 * @brief Calculates the variance of a signal.
 *
 * @param sig A reference to the signal.
 * @return The variance of the signal as a double.
 */
double variance(const Signal1 &sig);

/**
 * @brief Calculates the standard deviation of a signal.
 *
 * @param sig A reference to the signal.
 * @return The standard deviation of the signal as a double.
 */
double std_dev(const Signal1 &sig);

/**
 * @brief Divides a signal into overlapping frames.
 *
 * @param sig A reference to the signal.
 * @param frame_length The length of each frame.
 * @param hop_length The number of samples to step between frames.
 * @return A `Signal2` object containing the frames.
 */
Signal2 frame(const Signal1 &sig, unsigned frame_length, unsigned hop_length);

/**
 * @brief Normalizes a signal to have a specific range or property.
 *
 * @param sig A reference to the signal.
 * @return A normalized version of the signal.
 */
Signal1 normalized(const Signal1 &sig);

} // namespace muslib::mixer
