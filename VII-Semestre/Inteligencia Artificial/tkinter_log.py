from mpmath import mp
import numpy as np
from tkinter import *
import matplotlib
matplotlib.use('Tkagg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import time

toleranacia=0.00001
color="ro"

xs=[]
ys=[]
cs=[]
#regrecion lineal-------------------------para abajo
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
        if j==0:
            print("hay ceros")
        else:
            print("todo bien")
    # return
    return (-1/len(H))*sum(((e[0]*mp.log(e[1]))+((1-e[0])*mp.log(1-e[1])))for e in zip(Y,H))
def change_theta(X,Y,theta):
    alpha=0.0001
    H=h(theta,X)
    for j in range(0,len(theta)):
        var0=sum([(Y[i]-H[i])*(X[i][j])for i in range(0,len(Y))])
        theta[j]=theta[j]-(alpha*var0)
    return theta

def logistic():

    # data = np.loadtxt('wine.data.txt',delimiter=',')
    # x=data[:,1:13]
    # X=data[:,0:13]
    # Y=data[:,0]
    # for e in X:
    #     e[0]=1
    # # print(X)
    theta=[0.1,0.1]

    error=errorl(xs,ys,theta)
    count=0
    while error>=toleranacia:
        theta=change_theta(xs,ys,theta)
        error=errorl(xs,ys,theta)

        line.set_ydata([h(theta,[[1,0]]),h(theta,[[1,25]])])
        fig.canvas.draw()
        # count=count+1
        print("error ",error)

    print(theta)
#regrecion -------------------------para arriba
def onclick(event):
    print(color,' button=%d, x=%d, y=%d, xdata=%f, ydata=%f' %
          (event.button, event.x, event.y, event.xdata, event.ydata))
    xs.append([1,event.xdata])
    ys.append(event.ydata)

    if color=="ro":
        cs.append(0)
    else:
        cs.append(1)
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
    print(cs)
    # print(ys)


root = Tk()
root.title("graph regrecion")
# root.minsize(width=1500,height=1000)
# root.maxsize(width=800,height=800)
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
button4 = Button(root,text="lineal",command=logistic).grid(row=0,column=2)
button4 = Button(root,text="pr",command=fname).grid(row=0,column=3)
button4 = Button(root,text="      ",bg="green",command=change_color_green).grid(row=0,column=4)
cid = fig.canvas.mpl_connect('button_press_event', onclick)

FIGURE.get_tk_widget().grid(row=1,column=0,columnspan=5)
root.mainloop()
