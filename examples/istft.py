import librosa
import muslib
import librosa.display
import numpy as np
import matplotlib.pyplot as plt

filename = librosa.example('trumpet')
audio, sr = librosa.load(filename, sr=None)

n_fft = 1024
hop_length = 256

stft_result_muslib = muslib.transform.stft(
    audio,
    n_fft=n_fft,
    hop_length=hop_length)

stft_result_librosa = muslib.transform.stft(
    audio,
    n_fft=n_fft,
    hop_length=hop_length)

reconstructed_audio_muslib = muslib.transform.istft(
    stft_result_muslib, n_fft=n_fft, hop_length=hop_length)
reconstructed_audio_librosa = librosa.istft(
    stft_result_librosa, n_fft=n_fft, hop_length=hop_length)

plt.figure(figsize=(12, 10))

plt.subplot(2, 2, 1)
plt.plot(audio, label="Oryginalny sygnał", color="blue", alpha=0.7)
plt.title("Oryginalny sygnał")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()

plt.subplot(2, 2, 2)
plt.plot(reconstructed_audio_muslib, label="Zrekonstruowany sygnał (muslib)",
         color="green", alpha=0.7)
plt.title("Zrekonstruowany sygnał (muslib)")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()


plt.subplot(2, 2, 3)
plt.plot(audio, label="Oryginalny sygnał", color="blue", alpha=0.7)
plt.title("Oryginalny sygnał (copy)")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()
plt.subplot(2, 2, 4)
plt.plot(reconstructed_audio_librosa, label="Zrekonstruowany sygnał (librosa)",
         color="red", alpha=0.7)
plt.title("Zrekonstruowany sygnał (librosa)")
plt.xlabel("Czas (próbki)")
plt.ylabel("Amplituda")
plt.legend()

plt.tight_layout()
plt.show()
