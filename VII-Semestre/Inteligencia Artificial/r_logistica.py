import numpy as np
import math as mat
import matplotlib.pyplot as plt

toleranacia=0.00001

def prod(v1,v2):
    return sum([e[0]*e[1] for e in zip(v1,v2)])
def h(theta,X):
    return [prod(theta,e) for e in X]
def hlog(theta,X):
    return [1/(1+(np.exp(-1*e)))for e in h(theta,X)]
def convert_T_F(Yl):
    t_f=[]
    for e in Yl:
        if e<0.5:
            t_f.append(0)
        else:
            t_f.append(1)
    return t_f
def errorl(X,Y,theta):
    H=h(theta,X)
    print("\n")
    for j in H:
        if j<=0:
            print("es menor")
            return
    T=convert_T_F(H)
    print(H)
    return sum((e[0]*mat.log(e[1]))+((1-e[0])*mat.log(1-e[1]))for e in zip(T,H))*(-1/len(T))
def change_theta(X,Y,theta):
    alpha=0.01
    H=h(theta,X)
    T=convert_T_F(H)
    for j in range(0,len(theta)):
        var0=sum([(T[i]-H[i])*(X[i][j])for i in range(0,len(Y))])
        theta[j]=theta[j]-(alpha*var0)
    return theta

def logistic():

    data = np.loadtxt('wine.data.txt',delimiter=',')
    x=data[:,1:13]
    X=data[:,0:13]
    Y=data[:,0]
    for e in X:
        e[0]=1
    # print(X)
    theta=[0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1]

    print(len(theta))
    print(len(X[0]))
    error=errorl(X,Y,theta)
    # while error>=toleranacia:
    #     theta=change_theta(X,Y,theta)
    #     error=errorl(X,Y,theta)
    #     print("error ",error)
    #
    # print(theta)



logistic()
