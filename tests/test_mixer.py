import pytest
import muslib
import librosa
import numpy as np


# def test_chirp():
#     assert np.all(muslib.mixer.chirp(
#         fmin=110, fmax=110*64, duration=1, sr=22050) == librosa.chirp(
#         fmin=110, fmax=110*64, duration=1, sr=22050))
#


def test_tone():
    assert np.all(muslib.mixer.tone(440, duration=1, sr=22050)
                  == librosa.tone(440, duration=1, sr=22050))
    assert np.all(muslib.mixer.tone(440, sr=22050, length=22050)
                  == librosa.tone(440, sr=22050, length=22050))


def test_frame():
    y, _ = librosa.load(librosa.ex('trumpet'))
    frames_librosa = librosa.util.frame(y, frame_length=2048, hop_length=64)
    frames_muslib = muslib.mixer.frame(y, 2048, 64)
    assert np.allclose(frames_librosa, frames_muslib)


def test_zero_crossings():
    y = np.sin(np.linspace(0, 4 * 2 * np.pi, 20))
    assert np.all(muslib.mixer.zero_crossings(y)
                  == librosa.zero_crossings(y))


def test_zero_crossing_rate():
    y, _ = librosa.load(librosa.ex('trumpet'))
    res_l = librosa.feature.zero_crossing_rate(y)
    res_m = muslib.mixer.zero_crossing_rate(y)
    assert np.allclose(res_l, res_m)
