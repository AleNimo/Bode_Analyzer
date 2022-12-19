# -*- coding: utf-8 -*-
"""
Created on Wed Sep 21 16:25:15 2022

@author: Joaquin
"""


import numpy as np
import matplotlib.pyplot as plt


ciclos = 5

N0=ciclos * 4

T = 0.01

f = 1/T

fs = N0/(ciclos * T)



t = np.linspace(0, ciclos * T,N0,endpoint=False)

x = 15*np.sin(2*np.pi*f*t+np.pi/4)

plt.close('all')
plt.plot(t,x)

#x =np.array([1 ,2, 3 ,4 ,78 ,88, 96 ,74 ,55 ,55])
#N0=len(x)
x=np.append(x,0)
x=np.append(x,0)
x=np.append(x,0)



freq_bin = f


res_espectral = 2*np.pi/N0

k= int((freq_bin/fs * N0 ))
#k=1
wk = res_espectral * k

vk= np.zeros(N0+3)




for i in range(0,N0+1):
    vk[i+2] = x[i] + 2*np.cos(wk) * vk[i+1] - vk[i]


X_K = np.sqrt(vk[N0+2]**2+vk[N0-1+2]**2-2*np.cos(wk)*vk[N0+2]*vk[N0-1+2])/N0

print(X_K)