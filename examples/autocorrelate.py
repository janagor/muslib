import librosa
import muslib
import matplotlib.pyplot as plt

y, sr = librosa.load(librosa.ex('trumpet'))

odf = librosa.onset.onset_strength(y=y, sr=sr, hop_length=512)

librosa_ac = librosa.autocorrelate(odf)
muslib_ac = muslib.transform.autocorrelate(odf)

fig, ax = plt.subplots(ncols=2, figsize=(12, 5))

ax[0].plot(librosa_ac, label='librosa')
ax[0].set(title='Librosa Auto-correlation', xlabel='Lag (frames)')
ax[0].legend()

ax[1].plot(muslib_ac, label='muslib', color='orange')
ax[1].set(title='Muslib Auto-correlation', xlabel='Lag (frames)')
ax[1].legend()

plt.tight_layout()
plt.show()
