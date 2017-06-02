import numpy as np
import matplotlib.pyplot as plt
import sys

e,m,rhoe,rhom = np.loadtxt(sys.argv[1],unpack=True)
x=np.linspace(0,len(rhoe)-1,len(rhoe))

plt.figure(1)

plt.subplot(211)
plt.ylabel('rho e')

plt.plot(x,rhoe,'.-b')
plt.axhline(y=0, xmin=0, xmax=len(rhoe), hold=None)

plt.subplot(212)
plt.ylabel('rho m')

plt.plot(x,rhom,'.-b')
plt.axhline(y=0, xmin=0, xmax=len(rhoe), hold=None)
plt.show()


