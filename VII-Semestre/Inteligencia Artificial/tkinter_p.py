import numpy as np
from tkinter import *
import matplotlib
matplotlib.use('Tkagg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import time

lamda=10000000000
toleranacia=0.00001
color="ro"
# xs=[[1,1],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7],[1,8],[1,9]]
# ys=[1,2,3,4,5,6,7,8,9]
xs=[]
xs_p=[]
ys=[]
thetas_p=[]
cs=[]
#regreciacion lineal-------------------------para abajo
def prod(v1,v2):
    return sum([e[0]*e[1] for e in zip(v1,v2)])
def h(theta,X):
    return [prod(theta,e) for e in X]
def hlog(theta,X):
    return 1/(1-np.exp(-h(theta,X)))
def errorh(X,Y,theta):
    H=h(theta,X)
    sumreduc=sum(theta[1:])*lamda
    return sum([(e[0]-e[1])**2 for e in zip(Y,H)])/(2*len(Y))
    # return (sum([(e[0]-e[1])**2 for e in zip(Y,H)])+sumreduc)/(2*len(Y))
def change_theta(X,Y,theta):
    alpha=0.1
    H=h(theta,X)
    for j in range(0,len(theta)):
        var0=sum([(Y[i]-H[i])*-1*(X[i][j])for i in range(0,len(Y))])
        theta[j]=theta[j]-(alpha*var0)/len(Y)
        # theta[j]=theta[j]-((var0+(lamda*theta[j]))*(alpha/len(Y)))
    return theta

def regrecion():

    # for i in xs:
    #     xs_p.append([xs[0],xs[1],(xs[1])**2])
    #     thetas_p=np.random()

    theta=[1,1]

    error=errorh(xs,ys,theta)
    while error>=toleranacia:
        theta=change_theta(xs,ys,theta)
        error=errorh(xs,ys,theta)
        line.set_ydata([h(theta,[[1,0]]),h(theta,[[1,25]])])
        fig.canvas.draw()
        # time.sleep(0.2)
        print(error)
    print(theta)
#regreciacion -------------------------para arriba
def onclick(event):
    print(color,' button=%d, x=%d, y=%d, xdata=%f, ydata=%f' %
          (event.button, event.x, event.y, event.xdata, event.ydata))
    xs.append([1,event.xdata])
    ys.append(event.ydata)
    cs.append(color)
    points,= ax.plot(event.xdata,event.ydata,color)
    fig.canvas.draw()
    # print(xs,ys)
def change_color_green():
    global color
    color="go"
def change_color_red():
    global color
    color="ro"
def change_color_blue():
    global color
    color="bo"
def fname():
    print(xs)
    print(ys)


root = Tk()
root.title("graph regrecion")
# root.minsize(width=1500,height=1000)
# root.maxsize(width=800,height=800)
# plt.ion()
fig = plt.figure(figsize=(15,10))
ax = fig.add_subplot(1,1,1)
line,=ax.plot([0,25],[0,25])
fig.canvas.draw()

ax.axis([0,25,0,25])
# sticky=Defines how to expand the widget if the resulting cell is larger than the widget
 # itself. This can be any combination of the constants S, N, E, and W, or NW, NE, SW, and
 # SE.
FIGURE =FigureCanvasTkAgg(fig, master=root)
button1 = Button(root,text="Salir",command=root.quit).grid(row=0,column=4, sticky=E)
button2 = Button(root,text="      ",bg="red",command=change_color_red).grid(row=0,column=0)
button3 = Button(root,text="      ",bg="blue",command=change_color_blue).grid(row=0,column=1)
button4 = Button(root,text="lineal",command=regrecion).grid(row=0,column=2)
button4 = Button(root,text="pr",command=fname).grid(row=0,column=3)
button4 = Button(root,text="      ",bg="green",command=change_color_green).grid(row=0,column=4)
cid = fig.canvas.mpl_connect('button_press_event', onclick)

FIGURE.get_tk_widget().grid(row=1,column=0,columnspan=5)
root.mainloop()
