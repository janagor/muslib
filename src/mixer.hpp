#include "common.hpp"

namespace {
constexpr double default_phi = -std::numbers::pi * 0.5;
}

namespace muslib::mixer {
// TODO: to be implemented
Signal1 tone(double frequency, double sr = 22050, unsigned length = 0,
             double duration = -1, double phi = default_phi);
Signal1 chirp(double fmin, double fmax, double sr = 22050, int length = 0,
              double duration = -1, double phi = default_phi);
// Signal1 sin(double duration, unsigned sample_rate, double freq);
// Signal1 cos(double duration, unsigned sample_rate, double freq);
std::vector<bool> zero_crossings(const Signal1 &sig, bool pad = true);
Signal1 zero_crossing_rate(const Signal1 &sig, unsigned frame_length = 2048,
                           unsigned hop_length = 512);

/**
 * @brief Calculates the average of a signal.
 *
 * @param sig A reference to the signal.
 * @return The average value as a double.
 */
double avg(const Signal1 &sig);

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
