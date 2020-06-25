import numpy as np

namea="representation.testa"
nameb="representation.testb"
namet="representation.train"

print("loading",namea)

a=np.load('../data/'+namea+'.npy')
np.savetxt('../data/'+namea+'.csv', a, fmt="%f", delimiter=",")

print("loading",nameb)
b=np.load('../data/'+nameb+'.npy')
np.savetxt('../data/'+nameb+'.csv', b, fmt="%f", delimiter=",")

print("loading",namet)
c=np.load('../data/'+namet+'.npy')
np.savetxt('../data/'+namet+'.csv', c, fmt="%f", delimiter=",")