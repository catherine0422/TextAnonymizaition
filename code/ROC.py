#!/usr/bin/env python
# coding: utf-8

# In[11]:


import matplotlib.pyplot as plt
import numpy as np
import re

if __name__=="__main__":
    
    address = input('address: ')
    filename = input('txt file name: ')

    k = input('K:')
    data = input('Test data:')

    d = np.loadtxt(address+filename)

    X = d[:,0]
    Y = d[:,1]

    plt.plot(X,Y)
    plt.title('ROC curve, data ='+data+', k = '+k)
    plt.xlabel('false alarm rate')
    plt.ylabel('detection rate')
    plt.savefig(address+filename[:-4]+'.png')
    
    input('press to end')

