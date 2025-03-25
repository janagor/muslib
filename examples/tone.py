import numpy as np
import librosa
import muslib
import librosa.display
import matplotlib.pyplot as plt


fig, ax = plt.subplots(nrows=2, sharex=True, sharey=True)

tone1 = muslib.mixer.tone(440, duration=1, sr=22050)
S1 = librosa.feature.melspectrogram(y=tone1)
librosa.display.specshow(librosa.power_to_db(S1, ref=np.max),
                         x_axis='time', y_axis='mel', ax=ax[0])

tone2 = librosa.tone(440, duration=1, sr=22050)
S2 = librosa.feature.melspectrogram(y=tone2)
librosa.display.specshow(librosa.power_to_db(S2, ref=np.max),
                         x_axis='time', y_axis='mel', ax=ax[1])
plt.show()
