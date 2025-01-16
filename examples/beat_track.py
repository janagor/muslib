import numpy as np
import librosa
import muslib

y, sr = librosa.load(librosa.ex('nutcracker'), duration=10)
# y, sr = librosa.load(librosa.ex('choice'), duration=10)
tempo, beats = librosa.beat.beat_track(y=y, sr=sr)
a = muslib.beat.beat_track(y, sr)
print(a)
print(beats)

print(a.shape)
print(beats.shape)
