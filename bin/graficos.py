import numpy as np
import matplotlib.pyplot as plt
import sys

e,m,rhoe,rhom = np.loadtxt(sys.argv[1],unpack=True)
x=range(0,len(rhoe))

plt.figure(1)
plt.plot(x,rhoe,'b')
#plt.figure(2)
plt.plot(x,rhom,'r')
plt.figure(3)
plt.plot(x,e,'b')
#plt.figure(4)
plt.plot(x,m,'r')
plt.show()
