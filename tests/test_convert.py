import pytest
import muslib
import librosa
import numpy as np

in1 = 10
in2 = (1 + np.arange(10))
in3 = (1 + np.arange(100)).reshape(10, 10)
in4 = (1 + np.arange(1000)).reshape(10, 10, 10)
in5 = np.arange(0, 22050, 256)
in6 = 11025.0


def test_hz_to_mel():
    assert muslib.convert.hz_to_mel(in1) == librosa.hz_to_mel(in1)
    assert np.all(muslib.convert.hz_to_mel(in2) == librosa.hz_to_mel(in2))
    assert np.all(muslib.convert.hz_to_mel(in3) == librosa.hz_to_mel(in3))
    assert np.all(muslib.convert.hz_to_mel(in4) == librosa.hz_to_mel(in4))
    assert np.all(muslib.convert.hz_to_mel(in6) == librosa.hz_to_mel(in6))


def test_mel_to_hz():
    assert muslib.convert.mel_to_hz(in1) == librosa.mel_to_hz(in1)
    assert np.all(muslib.convert.mel_to_hz(in2) == librosa.mel_to_hz(in2))
    assert np.all(muslib.convert.mel_to_hz(in3) == librosa.mel_to_hz(in3))
    assert np.all(muslib.convert.mel_to_hz(in4) == librosa.mel_to_hz(in4))


def test_db_to_power():
    assert muslib.convert.db_to_power(in1) == librosa.db_to_power(in1)
    assert np.all(muslib.convert.db_to_power(in2) == librosa.db_to_power(in2))
    assert np.all(muslib.convert.db_to_power(in3) == librosa.db_to_power(in3))
    assert np.all(muslib.convert.db_to_power(in4) == librosa.db_to_power(in4))


def test_power_to_db():
    assert muslib.convert.power_to_db(in1) == librosa.power_to_db(in1)
    assert np.all(muslib.convert.power_to_db(in2) == librosa.power_to_db(in2))
    assert np.all(muslib.convert.power_to_db(in3) == librosa.power_to_db(in3))
    assert np.all(muslib.convert.power_to_db(in4) == librosa.power_to_db(in4))


def test_amplitude_to_db():
    assert muslib.convert.amplitude_to_db(in1) == librosa.amplitude_to_db(in1)
    assert np.all(muslib.convert.amplitude_to_db(in2)
                  == librosa.amplitude_to_db(in2))
    assert np.all(muslib.convert.amplitude_to_db(in3)
                  == librosa.amplitude_to_db(in3))
    assert np.all(muslib.convert.amplitude_to_db(in4)
                  == librosa.amplitude_to_db(in4))


def test_samples_to_frames():
    assert np.all(muslib.convert.samples_to_frames(in1)
                  == librosa.samples_to_frames(in1))
    assert np.all(muslib.convert.samples_to_frames(in2)
                  == librosa.samples_to_frames(in2))
    assert np.all(muslib.convert.samples_to_frames(in3)
                  == librosa.samples_to_frames(in3))
    assert np.all(muslib.convert.samples_to_frames(in4)
                  == librosa.samples_to_frames(in4))
    assert np.all(muslib.convert.samples_to_frames(in5)
                  == librosa.samples_to_frames(in5))


def test_frames_to_samples():
    y, sr = librosa.load(librosa.ex('choice'))
    _, beats = librosa.beat.beat_track(y=y, sr=sr)

    assert np.all(muslib.convert.frames_to_samples(beats)
                  == librosa.frames_to_samples(beats))
