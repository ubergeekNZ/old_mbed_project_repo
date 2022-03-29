# 2D/test_pylab2.py
import matplotlib.pyplot as plt
import numpy as np
import matplotlib
print 'matplotlib.__version__=', matplotlib.__version__

M = 1000

x = np.linspace(0, 2*np.pi, 100)
y = np.sin(x)

# You probably won't need this if you're embedding things in a tkinter plot...
plt.ion()

fig = plt.figure()
ax1 = fig.add_subplot(311)
line1, = ax1.plot(x, y, 'r-') # Returns a tuple of line objects, thus the comma
ax2 = fig.add_subplot(312)
line2, = ax2.plot(x, y, 'r-') # Returns a tuple of line objects, thus the comma
ax3 = fig.add_subplot(313)
line3, = ax3.plot(x, y, 'r-') # Returns a tuple of line objects, thus the comma


for i in range(M):
    # print 'iteration ', i
    phase = i/10.
    xp = x + phase

    # plot1
    line1.set_xdata(xp)
    line1.set_ydata(np.sin(xp))
    ax1.set_xlim(min(xp), max(xp))

    # plot2
    line2.set_xdata(xp)
    line2.set_ydata(np.sin(xp))
    ax2.set_xlim(min(xp), max(xp))

    # plot3
    line3.set_xdata(xp)
    line3.set_ydata(np.sin(xp))
    ax3.set_xlim(min(xp), max(xp))

    fig.canvas.draw()
    # fig.savefig('pylab2.png')