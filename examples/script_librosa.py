import librosa
import matplotlib.pyplot as plt
import numpy as np

y, sr = librosa.load('../data_examples/sine.wav') 

print('time:', librosa.get_duration(y=y, sr=sr))
print('probe frequency:', sr)

D = librosa.amplitude_to_db(librosa.stft(y), ref=np.max)
plt.figure(figsize=(10, 4))
librosa.display.specshow(D, y_axis='mel', x_axis='time')
plt.colorbar(format='%+2.0f dB')
plt.title('Mel-frequency spectrogram')
plt.tight_layout()
plt.show()

tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
print('Tempo:', tempo)

chroma_stft = librosa.feature.chroma_stft(y=y, sr=sr)
print('Chroma:', chroma_stft)