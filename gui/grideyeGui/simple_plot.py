import numpy
import matplotlib.pyplot as plt
import time
x = (1,2)
y = (1,2)
plt.ion()
plt.plot(x,y, 'r-')
plt.draw()

for i in range(100):
   print i
   time.sleep(1)
   plt.cla()
   y = (numpy.random.normal(), numpy.random.normal())
   plt.plot(x,y, 'r-')
   plt.draw()