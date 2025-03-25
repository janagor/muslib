import matplotlib.pyplot as plt
import librosa.display
import muslib
import librosa

y, sr = librosa.load(librosa.ex('trumpet'))

mfccs1 = librosa.feature.mfcc(y=y, sr=sr)
mfccs2 = muslib.transform.mfcc(y, sr)

plt.figure(figsize=(15, 6))

plt.subplot(1, 2, 1)
librosa.display.specshow(mfccs1, x_axis='time', sr=sr,
                         cmap='viridis', vmin=-50, vmax=20)
plt.colorbar(format='%+2.0f dB')
plt.title('MFCC - Librosa')
plt.ylabel('MFCC Coefficients')
plt.xlabel('Time (s)')

plt.subplot(1, 2, 2) 
librosa.display.specshow(mfccs2, x_axis='time', sr=sr,
                         cmap='viridis', vmin=-50, vmax=20)
plt.colorbar(format='%+2.0f dB')
plt.title('MFCC - Muslib')
plt.ylabel('MFCC Coefficients')
plt.xlabel('Time (s)')

plt.tight_layout()

plt.show()
