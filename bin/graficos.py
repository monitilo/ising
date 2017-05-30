import numpy as np
import matplotlib.pyplot as plt
import sys

T, E , sE, M , sM= np.loadtxt(sys.argv[1],unpack=True)

plt.figure(1)
plt.subplot(211)
plt.plot(T,np.abs(M),'.-b')
plt.subplot(212)
plt.plot(T,sM,'.-b')
plt.show()
