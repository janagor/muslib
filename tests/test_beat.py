import pytest
import muslib
import librosa
import numpy as np


def test_tempo():
    y, sr = librosa.load(librosa.ex('brahms'), duration=30)
    assert muslib.beat.tempo(y, sr) == librosa.feature.tempo(y=y, sr=sr)
    y, sr = librosa.load(librosa.ex('choice'), duration=30)
    assert muslib.beat.tempo(y, sr) == librosa.feature.tempo(y=y, sr=sr)
    y, sr = librosa.load(librosa.ex('nutcracker'), duration=30)
    assert muslib.beat.tempo(y, sr) == librosa.feature.tempo(y=y, sr=sr)
    y, sr = librosa.load(librosa.ex('trumpet'), duration=30)
    assert muslib.beat.tempo(y, sr) == librosa.feature.tempo(y=y, sr=sr)
