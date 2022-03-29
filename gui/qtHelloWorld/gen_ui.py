# -*- coding: utf-8 -*-
"""
Created on Thu Sep 20 08:07:37 2012

@author: bsb
"""

from PyQt4 import uic

fin = open('qtHelloWorld.ui','r')
fout = open('qtHelloWorld.py','w')
uic.compileUi(fin,fout,execute=False)
fin.close()
fout.close()