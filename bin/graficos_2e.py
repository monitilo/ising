import numpy as np
import matplotlib.pyplot as plt
import sys

T1, E1 , sE, M1 , sM= np.loadtxt(sys.argv[1],unpack=True)
T2, E2 , sE, M2 , sM= np.loadtxt(sys.argv[2],unpack=True)



f=open(sys.argv[1],'r')
aux=f.readline()
f.close()
aux1=aux.split(" ")
aux1=aux1[1]
aux1=aux1.split("=")
J1=float(aux1[1])
aux1=aux.split(" ")
aux1=aux1[2]
aux1=aux1.split("=")
B1=float(aux1[1])
f.close()

f=open(sys.argv[2],'r')
aux=f.readline()
f.close()
aux1=aux.split(" ")
aux1=aux1[1]
aux1=aux1.split("=")
J2=float(aux1[1])
aux1=aux.split(" ")
aux1=aux1[2]
aux1=aux1.split("=")
B2=float(aux1[1])
f.close()

xl=5
plt.figure(1)

plt.subplot(211)
plt.plot(T1,M1,'.-b')
plt.ylabel("M (B = " + str(B1) + ")")
plt.subplot(212)
plt.plot(T2,M2,'.-b')
plt.ylabel("M (B = " + str(B2) + ")")
plt.xlim(0,xl)
plt.savefig("frustracion.png")

plt.show()
