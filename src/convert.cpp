#include "convert.hpp"
#include <cmath>

namespace muslib::convert {

double hz_to_mel(double freq) {
  double F_MIN = 0.0;
  double F_SP = 200.0 / 3;

  auto mel = (freq - F_MIN) / F_SP;

  double MIN_LOG_HZ = 1000.0;
  double MIN_LOG_MEL = (MIN_LOG_HZ - F_MIN) / F_SP;
  double LOGSTEP = std::log(6.4) / 27.0;

  if (freq >= MIN_LOG_HZ)
    mel = MIN_LOG_MEL + std::log(freq / MIN_LOG_HZ) / LOGSTEP;

  return mel;
}
std::vector<double> hz_to_mel(const std::vector<double> &freqs) {
  double F_MIN = 0.0;
  double F_SP = 200.0 / 3;

  std::vector<double> mels(freqs);
  for (auto &mel : mels)
    mel = (mel - F_MIN) / F_SP;

  double MIN_LOG_HZ = 1000.0;
  double MIN_LOG_MEL = (MIN_LOG_HZ - F_MIN) / F_SP;
  double LOGSTEP = std::log(6.4) / 27.0;

  for (size_t i = 0; i < mels.size(); ++i)
    if (freqs.at(i) >= MIN_LOG_HZ)
      mels.at(i) = MIN_LOG_MEL + std::log(freqs.at(i) / MIN_LOG_HZ) / LOGSTEP;

  return mels;
}

double mel_to_hz(double mel) {
  double F_MIN = 0.0;
  double F_SP = 200.0 / 3;

  auto freq = F_MIN + F_SP * mel;

  double MIN_LOG_HZ = 1000.0;
  double MIN_LOG_MEL = (MIN_LOG_HZ - F_MIN) / F_SP;
  double LOGSTEP = std::log(6.4) / 27.0;

  if (mel >= MIN_LOG_MEL)
    freq = MIN_LOG_HZ * std::exp(LOGSTEP * (mel - MIN_LOG_MEL));

  return freq;
}

std::vector<double> mel_to_hz(const std::vector<double> &mels) {
  double F_MIN = 0.0;
  double F_SP = 200.0 / 3;

  std::vector<double> freqs(mels);
  for (auto &freq : freqs)
    freq = F_MIN + F_SP * freq;

  double MIN_LOG_HZ = 1000.0;
  double MIN_LOG_MEL = (MIN_LOG_HZ - F_MIN) / F_SP;
  double LOGSTEP = std::log(6.4) / 27.0;

  for (size_t i = 0; i < freqs.size(); ++i)
    if (mels.at(i) >= MIN_LOG_MEL)

      freqs.at(i) = MIN_LOG_HZ * std::exp(LOGSTEP * (mels.at(i) - MIN_LOG_MEL));

  return freqs;
}

std::vector<double> power_to_db(const std::vector<double> &signal) {
  std::vector<double> res(signal);
  for (auto &mel : res) {
    mel = 10 * std::log10(std::max(mel, 0.0000001));
  }
  return res;
}

std::vector<double> db_to_power(const std::vector<double> &signal) {
  std::vector<double> res(signal);
  for (auto &mel : res) {
    mel = std::pow(10., 0.1 * mel);
  }
  return res;
}

std::vector<double> amplitude_to_db(const std::vector<double> &signal) {
  std::vector<double> res(signal);
  for (auto &mel : res)
    mel = std::pow(mel, 2);
  return power_to_db(res);
}

std::vector<int> samples_to_frames(const std::vector<int> &samples,
                                   int hop_length, int n_fft) {
  int offset = n_fft / 2;
  std::vector<int> frames(samples);
  std::for_each(frames.begin(), frames.end(), [&](int &frame) {
    frame = std::floor(frame - offset) / hop_length;
  });
  return frames;
}

std::vector<int> frames_to_samples(const std::vector<int> &frames,
                                   int hop_length, int n_fft) {
  int offset = n_fft / 2;
  std::vector<int> samples(frames);
  std::for_each(samples.begin(), samples.end(),
                [&](int &sample) { sample = (sample * hop_length) + offset; });
  return samples;
}
} // namespace muslib::convert
