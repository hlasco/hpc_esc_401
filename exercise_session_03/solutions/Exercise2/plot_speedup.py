import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt('./speedup.txt')
for ncpus,time in data:
    if ncpus == 1:
        norm = time
        
data[:,1] = norm/data[:,1]

fig,ax = plt.subplots()
ax.plot(data[:,0],data[:,1],'s',label = 'real speedup')
ax.plot(np.arange(24),np.arange(24),label = 'ideal speedup')
ax.legend()
ax.set_xlabel('\#CPU')
ax.set_ylabel('Speedup')
fig.savefig('./speedup.png',dpi=350)
