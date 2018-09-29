# -*- coding: utf-8 -*-
"""
Created on Sat Sep 29 20:49:30 2018

@author: wmy
"""

from ctypes import *
import matplotlib.pyplot as plt

mydll = cdll.LoadLibrary('pydll1.dll')
mydll.PrintTime.restype = c_char_p
print(str(mydll.PrintTime()))

class SPID(Structure):
    
    __fields__ = [("kp", c_double),
                  ("ki", c_double),
                  ("kd", c_double),
                  ("set_point", c_double),
                  ("integration_sum", c_double),
                  ("p_term", c_double),
                  ("i_term", c_double),
                  ("d_term", c_double),
                  ("now_error", c_double),
                  ("last_error", c_double),]
    
    pass

PIDControlPositionType = mydll.PIDControlPositionType
PIDControlPositionType.restype = c_double
PIDControlPositionType.argtypes = [POINTER(SPID)]

pid = SPID()

mydll.PIDConfigure(byref(pid), c_double(0.45), c_double(0.025), c_double(0.03), c_double(100))

data = []

now = 0
data.append(now)

for i in range(200):   
    now = 2 * mydll.PIDControlPositionType(byref(pid), c_double(now))
    data.append(now)
    print(now)
    pass

plt.plot(data)



