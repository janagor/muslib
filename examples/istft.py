import librosa
import muslib
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

# Wczytaj plik audio
filename = librosa.example('trumpet')  # Przykładowy plik audio z librosa
# Wczytanie pliku z oryginalnym sample rate
audio, sr = librosa.load(filename, sr=None)

n_fft = 1024       # Rozmiar okna FFT
hop_length = 256   # Przesunięcie okna

stft_result = muslib.transform.stft(
    audio,
    n_fft=n_fft,
    hop_length=hop_length)


reconstructed_audio = muslib.transform.istft(
    stft_result, n_fft=n_fft, hop_length=hop_length)
print(reconstructed_audio.shape)
plt.figure(figsize=(12, 6))

# Wykres 1: Oryginalny sygnał
plt.subplot(2, 1, 1)
plt.plot(audio, label="Oryginalny sygnał", color="blue", alpha=0.7)
plt.title("Oryginalny sygnał")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()

# Wykres 2: Zrekonstruowany sygnał
plt.subplot(2, 1, 2)
plt.plot(reconstructed_audio, label="Zrekonstruowany sygnał",
         color="green", alpha=0.7)
plt.title("Zrekonstruowany sygnał (po STFT i ISTFT)")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()

plt.tight_layout()
plt.show()
