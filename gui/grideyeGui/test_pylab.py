from __future__ import division
from pylab import *

dx, dy = 0.01, 0.01
D = 0.01
dx2, dy2 = dx**2 ,dy**2
dt = (dx2*dy2)/(2*D*(dx2+dy2))
endt = 0.1
Nt = int (endt/dt)
endX,endY = 1,1
nx, ny = int(endX/dx), int(endY/dy)
T = zeros([nx,ny])
Tcopy = zeros([nx,ny])
"""initial conditions"""

for i in range(nx):
 for j in range(ny):
  if( ((i*dx - 0.5)**2 +(j*dy - 0.5)**2 < 0.1) and ((i*dx - 0.5)**2 +(j*dy - 0.5)**2 >0.05) ):
   T[i][j] = 10


def integrate(T,Tcopy):

 T[1:-1, 1:-1] = Tcopy[1:-1, 1:-1] + D*dt*( (Tcopy[2:, 1:-1] - 2*Tcopy[1:-1, 1:-1] + T[:-2, 1:-1])/dx2 + (Tcopy[1:-1, 2:] - 2*Tcopy[1:-1, 1:-1] + T[1:-1, :-2])/dy2  )
 Tcopy = copy(T)
 return Tcopy,T

x = arange(0, endX, dx)
y = arange(0, endY, dy)
X,Y = meshgrid(x, y)

"""creating the plot"""

fig, ax_lst = plt.subplots(1, 2)
ax_lst[0].imshow(T, interpolation='nearest',
                            origin='bottom',
                            aspect='auto',
                            vmin=np.min(T),
                            vmax=np.max(T),
                            cmap='hot',extent=[0,1,0,1])
im = ax_lst[1].imshow(T, interpolation='nearest',
                        origin='bottom',
                        aspect='auto',
                        vmin=np.min(T) + .01, # so 0 doesn't blow up the log
                        vmax=np.max(T),
                        cmap='hot',extent=[0,1,0,1],
                        norm=matplotlib.colors.LogNorm(clip=True),)
fig.colorbar(im)

"""main loop"""

for t in range(Nt):
 im.set_data(T)
 plt.draw()
 plt.pause(0.1)
 Tcopy,T = integrate(T,Tcopy)
 print np.mean(T), np.max(T), np.min(T)