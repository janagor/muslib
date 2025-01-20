import librosa
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

y, sr = librosa.load(librosa.ex('nutcracker'), duration=10)


tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
beat_times = librosa.frames_to_time(beat_frames, sr=sr)

# Generuj spektrogram
S = librosa.feature.melspectrogram(y=y, sr=sr, n_mels=128, fmax=8000)
S_dB = librosa.power_to_db(S, ref=np.max)

# Wizualizacja spektrogramu z zaznaczonymi bitami
plt.figure(figsize=(14, 8))
librosa.display.specshow(S_dB, x_axis='time', y_axis='mel',
                         sr=sr, fmax=8000, cmap='magma')
plt.colorbar(format='%+2.0f dB')
plt.title(f'Spektrogram z bitami (tempo: {tempo:.2f} BPM)', fontsize=16)

# Dodaj punkty odpowiadające bitom
plt.vlines(beat_times, ymin=0,
           ymax=S_dB.shape[0], color='cyan', alpha=0.8, linestyle='--', label='Bity')
plt.legend(loc='upper right')
plt.xlabel('Czas (s)')
plt.ylabel('Częstotliwość (Hz)')

# Zapis obrazu
plt.savefig('beat_spectrogram.png')
plt.show()


tempo, beats = librosa.beat.beat_track(y=y, sr=sr)
a = muslib.beat.beat_track(y, sr)
print(a)
print(beats)

print(a.shape)
print(beats.shape)
