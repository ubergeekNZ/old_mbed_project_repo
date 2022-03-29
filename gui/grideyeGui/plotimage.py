import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import numpy as np

A = np.array([28.00,
    27.50,
    28.75,
    28.25,
    30.00,
    29.25,
    30.50,
    30.50,
    27.50,
    26.75,
    27.75,
    28.00,
    28.00,
    28.25,
    28.50,
    29.00,
    26.75,
    26.00,
    26.75,
    27.75,
    28.25,
    28.00,
    28.00,
    28.25,
    25.50,
    26.00,
    26.25,
    26.75,
    27.75,
    26.75,
    27.50,
    27.75,
    26.00,
    25.75,
    25.25,
    26.25,
    27.00,
    27.00,
    27.75,
    27.00,
    26.25,
    25.75,
    26.00,
    26.25,
    26.00,
    26.50,
    25.50,
    24.00,
    25.75,
    26.00,
    25.50,
    25.25,
    26.25,
    27.00,
    25.25,
    26.00,
    25.00,
    25.00,
    25.50,
    24.75,
    25.75,
    26.50,
    26.50,
    24.50])
print A
B=np.reshape(A, (-1, 8))

print B

imgplot = plt.imshow(B,cmap='hot')
plt.colorbar(imgplot, orientation='vertical')
plt.grid(which='major', axis='both', linestyle='-')
plt.text(0,0,"hello")
plt.show()