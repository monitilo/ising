import numpy as np
import matplotlib.pyplot as plt
import sys

T, E , M = np.loadtxt(sys.argv[1],unpack=True)

plt.figure(1)
#plt.plot(T,np.abs(M),'.b')

plt.plot(T,M,'.-')

"""plt.figure(3)
plt.plot(x,e,'b')
#plt.figure(4)
plt.plot(x,m,'r')
"""
plt.show()
