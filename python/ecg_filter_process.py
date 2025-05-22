import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.signal import butter, filtfilt

cutoff_freq = 100
fs = 500 # Tan so lay mau ECG = 100Hz

# 1. Doc data tu file 
file_path = "D:/Esp-idf/Mysource/ad8232_ecg_test/data_text/NoFilter/data_ecg_noFilter_1st.csv"
df = pd.read_csv(file_path, header=None)
ecg_signal = df[0].values

if(len(ecg_signal) <= 15):
  raise ValueError("ECG signal to short ! At least 16 samples to read")

t = np.arange(len(ecg_signal)) / fs

def butterworth_LowPassFilter(data, cutoff, fs, order=4):
  nyquist_freq = 0.5 * fs
  normal_cutoff = cutoff / nyquist_freq
  b, a = butter(order, normal_cutoff, btype='low', analog=False)
  return filtfilt(b, a, data)

# Ap dung bo loc 
filtered_ecg = butterworth_LowPassFilter(ecg_signal, cutoff_freq, fs)

# Ve du lieu ra man hinh
plt.figure(figsize=(12, 6))
plt.plot(t, ecg_signal, label="Before ECG", alpha=0.5, color="gray")
plt.plot(t, filtered_ecg, label="After filtered ECG", linewidth=2, color="orange")
plt.xlabel("Time(s)")
plt.ylabel("Amptitude")
plt.title("ECG butterworth low pass filter")
plt.legend()
plt.grid()
plt.tight_layout()
plt.show()
