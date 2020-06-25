#!/usr/bin/env python
# coding: utf-8

# In[54]:


import numpy as np
from sklearn.decomposition import PCA
import sys
import pandas as pd

def label_preprocess(address = 'C:/Users/HP/Desktop/Kali/code/data/',
              classification_class = ['I-PER'],if_binary='N'):
    
           

    a = np.load(address+'true_labels.testa.npy')
    b = np.load(address+'true_labels.testb.npy')
    t = np.load(address+'true_labels.train.npy')

    print('shape a = ',np.shape(a))
    print('shape b = ',np.shape(b))
    print('shape t = ',np.shape(t))
    
    if if_binary=='Y':
        
        #input('XX')                         
        a = np.where(a=='I-PER',1,a)
        b = np.where(b=='I-PER',1,b)
        t = np.where(t=='I-PER',1,t)
        
        #input('XX')  
        a = np.where(a=='B-PER',1,a)
        b = np.where(b=='B-PER',1,b)
        t = np.where(t=='B-PER',1,t)
        
        for name in ['O','I-LOC','B-LOC','I-MISC','B-MISC','I-ORG','B-ORG']:
            a = np.where(a==name,0,a)
            b = np.where(b==name,0,b)
            t = np.where(t==name,0,t)

        pd.DataFrame(a).to_csv(address+"binary_labels_testa.csv",index = False,header=False)
        pd.DataFrame(b).to_csv(address+"binary_labels_testb.csv",index = False,header=False)
        pd.DataFrame(t).to_csv(address+"binary_labels_train.csv",index = False,header=False)
        
        
    else:
        all_name = ['O','I-PER','B-PER','I-LOC','B-LOC','I-MISC','B-MISC','I-ORG','B-ORG']
        name_label = []
        label = [0,1,2,3,4,5]
        for i in range(len(classification_class)):
            name = classification_class[i].split('-')[-1]
            if name not in name_label:
                name_label.append(name)
        
        for i in range(len(classification_class)):
        
            name = classification_class[i]
            all_name.remove(name)
            i = name_label.index(name.split('-')[-1])
        
            a = np.where(a==name,label[i],a)
            b = np.where(b==name,label[i],b)
            t = np.where(t==name,label[i],t)
           
    
        for name in all_name:
            a = np.where(a==name,label[len(name_label)],a)
            b = np.where(b==name,label[len(name_label)],b)
            t = np.where(t==name,label[len(name_label)],t)
    
        print(name_label,' is assigned to ', label[0:len(name_label)])
        print('other label is assigned to ', label[len(name_label)])
    
        pd.DataFrame(a).to_csv(address+"multi_labels_testa.csv",index = False,header=False)
        pd.DataFrame(b).to_csv(address+"multi_labels_testb.csv",index = False,header=False)
        pd.DataFrame(t).to_csv(address+"multi_labels_train.csv",index = False,header=False)

if __name__=="__main__":
    
    address = input('input address: ')
    if_binary = input('binary? Y/N : ')
    if if_binary=='N':
        classes = input('input list of class names: ')
    
        c = classes.split(',')
    
        label_preprocess(address,c)
    else:
        label_preprocess(address,if_binary='Y')
    input('input sth to stop')






