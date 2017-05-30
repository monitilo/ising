import numpy as np
import matplotlib.pyplot as plt
import sys

E, M= np.loadtxt(sys.argv[1],unpack=True)
x= np.arange(min(M),max(M)+1,1)
plt.figure(1)

plt.hist(M,x)

plt.show()
