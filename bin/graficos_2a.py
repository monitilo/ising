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

xl=50

plt.figure(1)

plt.subplot(211)
plt.plot(T,M,'ob',label="Experimento")
plt.plot(np.trim_zeros(T),32**2*np.tanh(B/np.trim_zeros(T)),'-r',linewidth=2.0,label='Teoria')
plt.xlim(0,xl)
plt.xlabel("T")
plt.ylabel("M")
plt.legend(loc='best')

plt.subplot(212)
plt.plot(T,E,'ob',label="Experimento")
plt.plot(np.trim_zeros(T) ,-32**2*B*np.tanh(B/np.trim_zeros(T)),'-r',linewidth=2.0,label='Teoria')
plt.xlim(0,xl)
plt.xlabel("T")
plt.ylabel("E")
plt.legend(loc='best')
plt.savefig("2a_B="+str(B)+".png")
plt.show()
