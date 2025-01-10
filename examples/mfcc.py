import matplotlib.pyplot as plt
import librosa.display
import muslib
import librosa

# Wczytanie pliku audio
y, sr = librosa.load(librosa.ex('trumpet'))

# Oblicz MFCC za pomocą librosa i muslib
mfccs1 = librosa.feature.mfcc(y=y, sr=sr)
mfccs2 = muslib.transform.mfcc(y, sr)

# Tworzenie wykresów obok siebie
plt.figure(figsize=(15, 6))

# Pierwszy wykres dla librosa
plt.subplot(1, 2, 1)  # 1 wiersz, 2 kolumny, wykres nr 1
librosa.display.specshow(mfccs1, x_axis='time', sr=sr,
                         cmap='viridis', vmin=-50, vmax=20)
# librosa.display.specshow(mfccs1, x_axis='time', sr=sr,
#                          cmap='viridis')
plt.colorbar(format='%+2.0f dB')
plt.title('MFCC - Librosa')
plt.ylabel('MFCC Coefficients')
plt.xlabel('Time (s)')

# Drugi wykres dla muslib
plt.subplot(1, 2, 2)  # 1 wiersz, 2 kolumny, wykres nr 2
librosa.display.specshow(mfccs2, x_axis='time', sr=sr,
                         cmap='viridis', vmin=-50, vmax=20)
# librosa.display.specshow(mfccs2, x_axis='time', sr=sr,
#                          cmap='viridis')
plt.colorbar(format='%+2.0f dB')
plt.title('MFCC - Muslib')
plt.ylabel('MFCC Coefficients')
plt.xlabel('Time (s)')

# Dostosowanie układu wykresów
plt.tight_layout()

# Wyświetlanie wykresów
plt.show()
