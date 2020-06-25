#!/usr/bin/env python
# coding: utf-8

# In[54]:





# In[ ]:


import numpy as np
from sklearn.decomposition import PCA
import sys
import pandas as pd


def PCA_(address = 'C:/Users/HP/Desktop/document/X-2A/INF442-analyse de donnees/proj/data1/data/',dimension = 64):
    
    print('loading file vectors')
    va = np.load(address+'representation.testa.npy')
    vb = np.load(address+'representation.testb.npy')
    vt = np.load(address+'representation.train.npy')
    
    print('ok')
    print('PCA-ing')
    pca=PCA(n_components=dimension)
    
    
    new_va=pca.fit_transform(va)
    print('testa keep a ratio of ',np.sum(pca.explained_variance_ratio_),' information')
    new_vb=pca.fit_transform(vb)
    print('testb keep a ratio of ',np.sum(pca.explained_variance_ratio_),' information')   
    new_vt=pca.fit_transform(vt)
    print('train keep a ratio of ',np.sum(pca.explained_variance_ratio_),' information')
    
    pd.DataFrame(new_va).to_csv(address+"data_testa_PCA_projected_d"+str(dimension)+".csv",index = False,header=False)
    pd.DataFrame(new_vb).to_csv(address+"data_testb_PCA_projected_d"+str(dimension)+".csv",index = False,header=False)
    pd.DataFrame(new_vt).to_csv(address+"data_testc_PCA_projected_d"+str(dimension)+".csv",index = False,header=False)
    
if __name__=="__main__":
    
    address = input('input address: ')
    d = input('input dimension: ')
    d = int(float(d))
    PCA_(address,d)
    input('press to end')

