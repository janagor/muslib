import librosa
import matplotlib.pyplot as plt
import numpy as np

y, sr = librosa.load('../data_examples/sine.wav') 

print('time:', librosa.get_duration(y=y, sr=sr))

tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
print('Tempo:', tempo)