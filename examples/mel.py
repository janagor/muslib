import numpy as np
import librosa
import muslib
import librosa.display
import matplotlib.pyplot as plt


fig, ax = plt.subplots(nrows=2, sharex=True, sharey=True)

mel1 = muslib.transform.mel(sr=22050, n_fft=2048)
img2 = librosa.display.specshow(mel1, x_axis='linear',  ax=ax[0])
ax[0].set(ylabel='Mel filter', title='Mel filter bank')
fig.colorbar(img2, ax=ax[0])

mel2 = librosa.filters.mel(sr=22050, n_fft=2048)
img2 = librosa.display.specshow(mel2, x_axis='linear',  ax=ax[1])
ax[1].set(ylabel='Mel filter', title='Mel filter bank')
fig.colorbar(img2, ax=ax[1])

plt.show()
