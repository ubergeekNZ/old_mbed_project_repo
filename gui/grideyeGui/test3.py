import numpy as np
import pylab as plt

# The number of divisions of the cmap we have
k = 10

# Random test data
A = np.random.random((10,10))*k

# First show without
plt.subplot(121)
plt.imshow(A,interpolation='nearest',cmap='YlOrRd')
plt.colorbar()

# Now label properly
plt.subplot(122)
plt.imshow(A,interpolation='nearest',cmap='YlOrRd')

cb = plt.colorbar()
labels = np.arange(0,k,1)
loc    = labels + .5
cb.set_ticks(loc)
cb.set_ticklabels(labels)

plt.show()