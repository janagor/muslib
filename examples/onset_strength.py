import matplotlib.pyplot as plt
import librosa
import muslib
import numpy as np


y, sr = librosa.load(librosa.ex('trumpet'), duration=3)
D = np.abs(librosa.stft(y))
times = librosa.times_like(D, sr=sr)
fig, ax = plt.subplots(nrows=1, sharex=False)

onset_env = muslib.beat.onset_strength(y, sr)
ax.plot(times[0:-2], 2 + onset_env / onset_env.max(), alpha=0.8,
        label='Mean (mel) muslib')
onset_env = librosa.onset.onset_strength(y=y, sr=sr)
ax.plot(times, 2 + onset_env / onset_env.max(), alpha=0.8,
        label='Mean (mel) librosa')

ax.legend()
ax.set(ylabel='Normalized strength', yticks=[])


plt.show()
