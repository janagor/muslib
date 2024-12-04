import muslib

#todo

signal = muslib.load('../data_examples/sine.wav')

print('time', librosa.get_duration())

tempo = librosa.estimate_tempo(signal)
print('tempo', tempo)