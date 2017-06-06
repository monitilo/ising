import numpy as np
import matplotlib.pyplot as plt
import sys

T, E , sE, M , sM= np.loadtxt(sys.argv[1],unpack=True)

f=open(sys.argv[1],'r')
aux=f.readline()
f.close()
aux=aux.split(" ")
aux=aux[1]
aux=aux.split("=")
B=float(aux[1])

plt.figure(1)

plt.subplot(211)
plt.plot(T,M,'.-b')
plt.plot(np.trim_zeros(T),32**2*np.tanh(B/np.trim_zeros(T)),'.-r')
plt.subplot(212)
plt.plot(T,sM,'.-b')
plt.show()
