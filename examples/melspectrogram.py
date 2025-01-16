import numpy as np
import librosa
import muslib
import librosa.display
import matplotlib.pyplot as plt
import time

y, sr = librosa.load(librosa.ex('trumpet'))


t1 = time.time()

S2 = muslib.transform.melspectrogram(y, sr=sr)

t2 = time.time()

S1 = librosa.feature.melspectrogram(y=y, sr=sr)

t3 = time.time()

print("my: ", t2-t1)
print("their: ", t3-t2)


fig, ax = plt.subplots(nrows=2, sharex=True, sharey=True)

S1_dB = librosa.power_to_db(S1, ref=np.max)
img = librosa.display.specshow(S1_dB, x_axis='time',
                               y_axis='mel', sr=sr,
                               fmax=8000, ax=ax[0])
fig.colorbar(img, ax=ax[0], format='%+2.0f dB')
ax[0].set(title='Mel-frequency spectrogram')

S2_dB = librosa.power_to_db(S2, ref=np.max)
img = librosa.display.specshow(S2_dB, x_axis='time',
                               y_axis='mel', sr=sr,
                               fmax=8000, ax=ax[1])
fig.colorbar(img, ax=ax[1], format='%+2.0f dB')
ax[1].set(title='Mel-frequency spectrogram')

plt.show()
