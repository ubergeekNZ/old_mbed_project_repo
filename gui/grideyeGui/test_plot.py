#!/usr/bin/env python
'''
Make a set of images with a single colormap, norm, and colorbar.

It also illustrates colorbar tick labelling with a multiplier.
'''
import time
from matplotlib.pyplot import figure, show, axes, sci
from matplotlib import cm, colors
from matplotlib.font_manager import FontProperties
from numpy import amin, amax, ravel, zeros, random
from numpy.random import rand


Nr = 2
Nc = 1

fig = figure(figsize=(8,8))
cmap = cm.cool

figtitle = 'Multiple images'
t = fig.text(0.5, 0.95, figtitle,
               horizontalalignment='center',
               fontproperties=FontProperties(size=16))

# Remove color bar by commented it out
# cax = fig.add_axes([0.2, 0.08, 0.6, 0.04])
# 
zero = zeros((8, 8), dtype=float)

w = 0.5
h = 0.5
ax = []


# first figure
pos = [0.075, 0.18, w, h]
a = fig.add_axes(pos)
imgplot = a.imshow(zero, cmap='YlOrRd', interpolation='nearest', vmin = 15.0, vmax = 30.0)
ax.append(a)

# pos = [0.1, 0.25, w, h]
# b = fig.add_axes(pos)
# dd = ravel(zero)
# vmin = min(vmin, amin(dd))
# vmax = max(vmax, amax(dd))
# images.append(b.imshow(zero, cmap=cmap, interpolation='nearest', vmin = 16.0, vmax = 25.0))
# ax.append(b)

show()

N = 8

# loop and update diagrams

for i in range(0,100):
    # pos = [0.075, 0.18, w, h]
    # a = fig.add_axes(pos)
    random_data = random.random((N,N))
    imgplot.set_data(random_data)
    print random_data
    a.clf()
    a.imshow(random_data,cmap='YlOrRd', interpolation='nearest', vmin = 15.0, vmax = 30.0)
    a.draw()
    time.sleep(2)
