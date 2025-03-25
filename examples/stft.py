import numpy as np
import librosa
import muslib
import librosa.display
import matplotlib.pyplot as plt

y, sr = librosa.load(librosa.ex('trumpet'))

S1 = np.abs(librosa.stft(y))
S2 = np.abs(muslib.transform.stft(y))

fig, ax = plt.subplots(nrows=2, sharex=True, sharey=True)

img1 = librosa.display.specshow(librosa.amplitude_to_db(
    S1, ref=np.max), y_axis='log', x_axis='time', ax=ax[0])
ax[0].set_title('Power spectrogram')
fig.colorbar(img1, ax=ax[0], format="%+2.0f dB")

img2 = librosa.display.specshow(librosa.amplitude_to_db(
    S2, ref=np.max), y_axis='log', x_axis='time', ax=ax[1])
ax[1].set_title('Power spectrogram')
fig.colorbar(img2, ax=ax[1], format="%+2.0f dB")

plt.show()
