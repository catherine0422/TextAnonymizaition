#!/usr/bin/env python
# coding: utf-8

# In[26]:


import numpy as np
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis
import pandas as pd


# In[23]:


if __name__=="__main__":
    
    address = input('address: ')
    # a = np.load(address+'true_labels.testa.npy')
    # b = np.load(address+'true_labels.testb.npy')
    t = np.load(address+'true_labels.train.npy')
    data_a = np.load(address+'representation.testa.npy')
    data_b = np.load(address+'representation.testb.npy')
    data = np.load(address+'representation.train.npy')
    #print(np.shape(data))
    
    num = int(input('Use how many points to train the model? < 203593 : '))
    tsmall = t[0:num]
    datasmall = data[0:num,:]
    
    n = int(input('target dimentionality (output d can be smaller than this according to the dataset) : '))
    print('training')
    
    lda = LinearDiscriminantAnalysis(n_components=n)
    lda.fit(datasmall,tsmall)
    print('fitting')
    newrept = lda.transform(data)
    newrepa = lda.transform(data_a)
    newrepb = lda.transform(data_b)
    
    pd.DataFrame(newrepa).to_csv(address+"representation_testa_LDA_projected_d"+str(n)+".csv",index = False,header=False)
    pd.DataFrame(newrepb).to_csv(address+"representation_testb_LDA_projected_d"+str(n)+".csv",index = False,header=False)
    pd.DataFrame(newrept).to_csv(address+"representation_train_LDA_projected_d"+str(n)+".csv",index = False,header=False)
    
    input('press to end')


# In[ ]:





# In[ ]:





# In[44]:





# In[ ]:





# In[28]:




