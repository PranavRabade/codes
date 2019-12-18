#!/usr/bin/env python
# coding: utf-8

# In[35]:


import pandas as pd
import numpy as np
import random as rd
data = pd.read_csv('audit_risk.csv')


# In[36]:

def activation(temp, threshold = 150):
    if temp > threshold:
        return 1
    return -1


# In[37]:


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
p = np.array(p)
desired = np.array(desired)
p.shape


# In[38]:

# Extracting training and testing data
indices = rd.sample([i for i in range(60)], k = 30)
train_data = list()
test_data = list()
for i in indices:
    test_data.append(p[i])
indices = list(set([i for i in range(60)])^set(indices))
for i in indices:
    train_data.append(p[i])
desired = np.array(desired)
train_data = np.array(train_data)
test_data = np.array(test_data)
# Training and testing data extracted.
print('Training and testing data extracted')


# In[39]:


# Initializing Weight Vector 
W = np.array([0 for i in range(6)])
# Initializing Input Data Pattern
p = train_data
X = p[0]
# Declaring number of Epochs
epochs = 100
# Initializing initial learning_rate
learning_rate = 1
correct = 0


# In[40]:


print('Training Begins : ')
while epochs > 0:
    epochs -= 1
    for i in range(p.shape[0]):
        #print(i)
        X = p[i]
        temp = activation(np.dot(np.transpose(W), X))
        #print('Pattern', i + 1, 'classified', end = ' ')
        if (temp == -1 and desired[i] == 0) or (temp == desired[i]):
            #print('correctly')
            correct += 1
        wt_change = learning_rate*(desired[i] - temp)*X
        W = W + wt_change
print('Correct Classifications : ', correct, '/ 60000')
print('Accuracy : ', correct/60000*100)
print('Weight Vector : ', W)


# In[41]:


# Testing Phase:
print('Initializing Testing Phase : ')
p = test_data
print(p.shape)
correct = 0
for i in range(len(p)):
    op = activation(np.dot(np.transpose(W), p[i]))
    if (temp == -1 and desired[i] == 0) or (temp == desired[i]):
            #print('correctly')
            correct += 1
print('No. Of correct Test Classifications : ', correct, ' / 30')
print('Accuracy : ', correct / 30*100)


# In[ ]:




