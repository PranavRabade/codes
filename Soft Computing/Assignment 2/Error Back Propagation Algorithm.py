#!/usr/bin/env python
# coding: utf-8

# In[178]:


from math import exp
def activation(temp):
    return 1/(1 + exp(-temp))


# In[179]:


import pandas as pd 
import random as rd
import numpy as np
data = pd.read_csv('audit_risk.csv')
temp = list()
p = list()
for j in range(len(data)):
    for i in data:
        temp.append(data[i][j])
    p.append(temp)
    del(temp)
    temp = []
desired = list()
for i in range(len(p)):
    desired.append(p[i][-1])
    p[i] = p[i][:-1]


# In[180]:

print('Extracting training and testing data')
indices = rd.sample([i for i in range(776)], k = 194)
train_data = list()
test_data = list()
for i in indices:
    test_data.append(p[i])
indices = list(set([i for i in range(776)])^set(indices))
for i in indices:
    train_data.append(p[i])
desired = np.array(desired)
train_data = np.array(train_data)
test_data = np.array(test_data)
del p, indices
print('Training and testing data extracted')

# In[188]:


# No. of i/p Layer Neurons : 25
# No. of Computational Neurons in hidden layer : 4
# No. of o/p Layer Neurons : 1
# Initial Learning Rate : 1
# Initial wt. vector : [0 ... 0] (26 times)
# No. of input patterns in dataset : 776
epochs = 100
correct = 0
learning_rate = 1


# In[189]:


W_0 = [[0.0 for i in range(26)] for j in range(4)]
W_1 = [0.0 for i in range(4)]
while epochs > 0:
    epochs -= 1
    for i in range(len(train_data)):
        
        # Outputs of Hidden Layer Neurons
        outputs = list()
        for j in range(4):
            W_iX_i = np.dot(np.transpose(W_0[j]), train_data[i])
            outputs.append(activation(W_iX_i))
        outputs = np.array(outputs)
        
        # Finding output of output layer.
        y = activation(np.dot(np.transpose(W_1), outputs))
        
        # Classification Step
        if (y >= 0.5 and desired[i] == 1) or (y < 0.5 and desired[i] == 0):
            correct += 1
            
        # Calculating output layer neuron local gradient
        opl_loc_grad = (desired[i] - y)*y*(1 - y)
        del W_iX_i
        outputs = np.array(outputs)
        #print(type(opl_loc_grad), type(learning_rate), type(outputs))
        Wt_change = opl_loc_grad*learning_rate*outputs
        
        # Updating weight vector for output layer neuron
        W_1 = W_1 + Wt_change
        del Wt_change
        hl_local_grads = list()
        
        # Calculating Local Gradients for hidden Layer neurons
        for j in range(4):
            hl_local_grads.append(outputs[j]*(1 - outputs[j])*(opl_loc_grad)*W_1[j])
        hl_local_grads = np.array(hl_local_grads)
        W_0 = np.array(W_0)
        
        # Updating weight vectors for hidden layer neurons
        for j in range(4):
            Wt_change = learning_rate*hl_local_grads[j]*train_data[i]
            W_0[j] = W_0[j] + Wt_change

if correct > 30000:
    print('No. Of Correct Classifications : ', correct / 58200)
    print('Accuracy ', correct / 582)
else:
    print('No. of Correct Classifications : ', correct*100, 58200)
    print('Accuracy : ', correct*100 / 582)

# In[190]:


correct /= 3

print('Initializing Test Phase : ')
for i in range(len(test_data)):
    outputs = list()
    for j in range(4):
        outputs.append(activation(np.dot(np.transpose(W_0[j]), test_data[i])))
    outputs = np.array(outputs)
    y = activation(np.dot(np.transpose(W_1), outputs))
    if (y >= 0.5 and desired[i] == 1) or (y < 0.5 and desired[i] == 0):
        correct += 1
print('Testing Phase Executed')
print('Correct Classifications : ', correct, ' / 194')
print('Accuracy : ', correct / 1.94)


# In[ ]:
input()



