import numpy as np
import matplotlib.pyplot as plt
import sys

T, E , sE, M , sM= np.loadtxt(sys.argv[1],unpack=True)

f=open(sys.argv[1],'r')
aux=f.readline()
f.close()
aux1=aux.split(" ")
aux1=aux1[1]
aux1=aux1.split("=")
J=float(aux1[1])
aux1=aux.split(" ")
aux1=aux1[2]
aux1=aux1.split("=")
B=float(aux1[1])

plt.figure(1)

plt.subplot(211)
plt.plot(T,M,'.-b')
plt.ylabel("M")
plt.subplot(212)
plt.plot(T,E,'.-b')
plt.ylabel("E")
plt.show()
