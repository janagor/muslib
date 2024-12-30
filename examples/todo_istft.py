import librosa
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

# Wczytaj plik audio
filename = librosa.example('trumpet')  # Przykładowy plik audio z librosa
# Wczytanie pliku z oryginalnym sample rate
audio, sr = librosa.load(filename, sr=None)

# Parametry STFT
n_fft = 1024       # Rozmiar okna FFT
hop_length = 256   # Przesunięcie okna
win_length = 1024  # Długość okna (zwykle taka sama jak n_fft)
window = 'hann'    # Typ okna

# Obliczenie STFT
stft_result = librosa.stft(
    audio, n_fft=n_fft, hop_length=hop_length, win_length=win_length, window=window)

# Odwrócenie STFT (rekonstrukcja sygnału czasowego)
reconstructed_audio = librosa.istft(
    stft_result, hop_length=hop_length, win_length=win_length, window=window)

# Tworzenie wykresów
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
