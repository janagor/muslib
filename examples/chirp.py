import numpy as np
import librosa
import muslib
import librosa.display
import matplotlib.pyplot as plt

linear_chirp1 = muslib.mixer.chirp(
    fmin=110, fmax=110*64, duration=1,  sr=22050)
linear_chirp2 = librosa.chirp(
    fmin=110, fmax=110*64, duration=1, linear=True, sr=22050)

fig, ax = plt.subplots(nrows=2, sharex=True, sharey=True)

S_exponential = np.abs(librosa.stft(y=linear_chirp1))
librosa.display.specshow(librosa.amplitude_to_db(S_exponential, ref=np.max),
                         x_axis='time', y_axis='linear', ax=ax[0])
ax[0].set(title='Exponential chirp', xlabel=None)
ax[0].label_outer()

S_linear = np.abs(librosa.stft(y=linear_chirp2))
librosa.display.specshow(librosa.amplitude_to_db(S_linear, ref=np.max),
                         x_axis='time', y_axis='linear', ax=ax[1])
ax[1].set(title='Linear chirp')
plt.show()
