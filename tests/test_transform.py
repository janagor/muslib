import pytest
import muslib
import librosa
import numpy as np


def test_mel_frequencies():
    assert np.all(muslib.transform.mel_frequencies(
        40) == librosa.mel_frequencies(n_mels=40))


def test_tempo_frequencies():
    assert np.all(muslib.transform.tempo_frequencies(
        40) == librosa.tempo_frequencies(40))


def test_mel():
    assert np.allclose(muslib.transform.mel(sr=22050, n_fft=2048),
                       librosa.filters.mel(sr=22050, n_fft=2048))
    assert np.allclose(muslib.transform.mel(sr=22050, n_fft=2048),
                       librosa.filters.mel(sr=22050, n_fft=2048))


def test_fft_frequencies():
    assert np.allclose(muslib.transform.fft_frequencies(sr=22050, n_fft=16),
                       librosa.fft_frequencies(sr=22050, n_fft=16))
    assert np.allclose(muslib.transform.fft_frequencies(sr=22050, n_fft=2048),
                       librosa.fft_frequencies(sr=22050, n_fft=2048))
