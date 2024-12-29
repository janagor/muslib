import pytest
import muslib
import librosa
import numpy as np
print(muslib.mixer.chirp(
    fmin=110, fmax=110*64, duration=1, sr=22050).shape)
print(librosa.chirp(
    fmin=110, fmax=110*64, duration=1, sr=22050).shape)
print(np.max(muslib.mixer.chirp(
    fmin=110, fmax=110*64, duration=1, sr=22050) - librosa.chirp(
    fmin=110, fmax=110*64, duration=1, sr=22050)))


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
