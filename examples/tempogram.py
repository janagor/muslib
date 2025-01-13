import muslib
import librosa
import numpy as np
import librosa.display
import matplotlib.pyplot as plt

audio_file = librosa.example('choice')
y, sr = librosa.load(audio_file, sr=None)

tempogram_librosa = librosa.feature.tempogram(y=y, sr=sr)
tempogram_muslib = muslib.beat.tempogram(y, sr)

plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
librosa.display.specshow(
    tempogram_librosa, sr=sr, hop_length=512,
    x_axis='time', y_axis='tempo', cmap='magma'
)
plt.colorbar(label='Tempo Strength')
plt.title('Tempogram (Librosa)')
plt.xlabel('Time (s)')
plt.ylabel('Tempo (BPM)')

plt.subplot(1, 2, 2)
librosa.display.specshow(
    tempogram_muslib, sr=sr, hop_length=512,
    x_axis='time', y_axis='tempo', cmap='magma'
)
plt.colorbar(label='Tempo Strength')
plt.title('Tempogram (Muslib)')
plt.xlabel('Time (s)')
plt.ylabel('Tempo (BPM)')

plt.tight_layout()
plt.show()
