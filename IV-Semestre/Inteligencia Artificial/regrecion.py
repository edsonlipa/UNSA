import numpy as np
import matplotlib.pyplot as plt

toleranacia=0.00001

def prod(v1,v2):
    return sum([e[0]*e[1] for e in zip(v1,v2)])
def h(theta,X):
    return [prod(theta,e) for e in X]
def hlog(theta,X):
    return 1/(1-np.exp(-h(theta,X)))
def errorh(X,Y,theta):
    H=h(theta,X)
    return sum([(e[0]-e[1])**2 for e in zip(Y,H)])/(2*len(Y))
def change_theta(X,Y,theta):
    alpha=0.01
    H=h(theta,X)
    for j in range(0,len(theta)):
        var0=sum([(Y[i]-H[i])*-1*(X[i][j])for i in range(0,len(Y))])
        theta[j]=theta[j]-(alpha*var0)
    return theta

def main():
    X=[[1,0],[1,1],[1,2],[1,3],[1,4],[1,5]]
    x=[]
    for i in range(0,len(X)):
        x.append(X[i][1])

    Y=[0,1,2,3,4,5]
    theta=[0.1,0.1]

    gx=[0,10]
    gy=[h(theta,[[1,0]]),h(theta,[[1,10]])]
    plt.ion()
    ax=plt.gca()
    #ax.set_autoscale_on(True)
    points,= ax.plot(x,Y,"ro")
    line,=ax.plot(gx,gy)
    plt.draw()
    plt.pause(1)

    error=errorh(X,Y,theta)
    while error>=toleranacia:
        theta=change_theta(X,Y,theta)
        error=errorh(X,Y,theta)
        line.set_ydata([h(theta,[[1,0]]),h(theta,[[1,10]])])
        plt.draw()
        plt.pause(0.1)

        print(error)

    print(theta)



main()
