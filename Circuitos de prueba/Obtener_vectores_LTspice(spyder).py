# -*- coding: utf-8 -*-
"""
Created on Wed Nov 30 13:49:29 2022

@author: Alejo
"""

import ltspice
import numpy as np

l = ltspice.Ltspice("./Circuito.raw")
l.parse()

#Obtengo curvas de simulación en ltspice
freq = l.get_frequency()
vout = l.get_data('V(vo)')

mod = 20*np.log(np.abs(vout))
phase = np.unwrap(np.angle(vout))
