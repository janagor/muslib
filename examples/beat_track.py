import librosa
import muslib
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

y, sr = librosa.load(librosa.ex('nutcracker'), duration=10)
fig, ax = plt.subplots(2, 1, figsize=(14, 12))

tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
beat_times = librosa.frames_to_time(beat_frames, sr=sr)


ax[0].set_title(f'Spektrogram Librosa (tempo: {tempo} BPM)', fontsize=16)
ax[0].set_xlabel('Czas (s)')
ax[0].set_ylabel('Częstotliwość (Hz)')
ax[0].vlines(beat_times, ymin=0, ymax=S_dB.shape[0], color='cyan',
             alpha=0.8, linestyle='--', label='Bity')
ax[0].legend(loc='upper right')


beat_frames_muslib = muslib.beat.beat_track(y, sr)
tempo = muslib.beat.tempo(y, sr)
beat_times = librosa.frames_to_time(beat_frames_muslib, sr=sr)

ax[1].set_title(f'Spektrogram Muslib (tempo: {tempo} BPM)', fontsize=16)
ax[1].set_xlabel('Czas (s)')
ax[1].set_ylabel('Częstotliwość (Hz)')
ax[1].vlines(beat_times, ymin=0, ymax=S_dB.shape[0], color='cyan',
             alpha=0.8, linestyle='--', label='Bity')
ax[1].legend(loc='upper right')

plt.tight_layout()
plt.show()
