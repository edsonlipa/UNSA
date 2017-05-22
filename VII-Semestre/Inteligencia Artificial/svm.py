import numpy as np
from Tkinter import *
import matplotlib
matplotlib.use('Tkagg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
import time
import cvxopt
import cvxopt.solvers



pos = []
neg = []
color="ro"

def linear_kernel(x1, x2):
    return np.dot(x1, x2)

class SVM(object):
    def __init__(self, kernel=linear_kernel, C=None):
        print("INICIANDO")
        self.kernel = kernel
        self.C = C

    #ajustamos los datos para hallar los multiplicadores de lagrange
    def hallar(self, X, y):

        n_samples, n_features = X.shape
        print("SHAPE")
        print(n_samples)
        #Inicializo mi matriz

        K = np.zeros((n_samples, n_samples))
        for i in range(n_samples):
            for j in range(n_samples):
                K[i,j] = linear_kernel(X[i], X[j])

        P = cvxopt.matrix(np.outer(y,y) * K)
        q = cvxopt.matrix(np.ones(n_samples) * -1)
        A = cvxopt.matrix(y, (1,n_samples))
        b = cvxopt.matrix(0.0)
        G = cvxopt.matrix(np.diag(np.ones(n_samples) * -1))
        h = cvxopt.matrix(np.zeros(n_samples))
        # Resolver un Programa Cuadratico
        solution = cvxopt.solvers.qp(P, q, G, h, A, b)

        print("IMPRIMIENDO K \n")
        print(K)
        #en una sola fila
        multi = np.ravel(solution['x'])
        # sv vector booleano true > 1e-5
        sv = multi > 1e-5
        print("IMPRIMIENDO MULTI \n")
        print(multi)
        ind = np.arange(len(multi))[sv]
        indt = np.arange(len(multi))
        print("IMPRIMIENDO IND \n")
        print(indt)
         #---------------------
        print("IMPRIMIENTO SV:")
        print(sv)
        self.a = multi[sv]
        print("IMPRIMIENTO A:")
        print(self.a)
        self.sv = X[sv]
        print("IMPRIMIENTO XSV:")
        print(self.sv)
        self.sv_y = y[sv]
        print("IMPRIMIENTO SV_Y:")
        print(self.sv_y)

        # Hallamos la intercepto b
        self.b = 0
        for n in range(len(self.a)):
            self.b += self.sv_y[n]
            #Sumatoria de a * y
            self.b -= np.sum(self.a * self.sv_y * K[ind[n],sv]) #* K[ind[n],sv] = y
        self.b = self.b/len(self.a)
        print("IMPRIMIENTO B:")
        print(self.b)

        # Hallamos el peso del vector w
        self.w = np.zeros(n_features)
        #Sumatoria a_i*y_i*x_i a multiplicador de lagrange
        for n in range(len(self.a)):
            self.w += self.a[n] * self.sv_y[n] * self.sv[n]

        print("IMPRIMIENTO W:")
        print(self.w)
    #PARA GRAFICAR
    def project(self, X):
        return np.dot(X, self.w) + self.b

def fix():
     y1 = np.ones(len(pos))
     y2 = np.ones(len(neg)) * -1
     X = np.vstack((pos, neg)) #[[1,2,3],[4,5,6]]
     y = np.hstack((y1, y2)) #[1,1,1...-1,-1,-1]
     print("Xs")
     print(X)
     X_train = X
     y_train = y
     f = SVM(C=0.1)
     f.hallar(X_train, y_train)
     plotear(f)
def plotear(f):
    X1, X2 = np.meshgrid(np.linspace(0,25,10), np.linspace(-0,25,10))
    X = np.array([[x1, x2] for x1, x2 in zip(np.ravel(X1), np.ravel(X2))])

    Z = f.project(X).reshape(X1.shape)
    print("IMPRIMIENDO X1:")
    print(X1)
    print("IMPRIMIENDO X2:")
    print(X2)

    print("IMPRIMIENDO Z:")
    print(Z)
    # line0,=ax.plot([0,25],[0,25])
    # line1,=ax.plot([0,25],[0,25])
    # line2,=ax.plot([0,25],[0,25])
    ax.contour(X1, X2, Z,[0.0], colors='y', linewidths=1)
    ax.contour(X1, X2, Z + 1, colors='black', linewidths=1)
    ax.contour(X1, X2, Z - 1, [0.0], colors='black', linewidths=1)

    # plt.axis("tight")
    plt.show()
def onclick(event):
    print(color,' button=%d, x=%d, y=%d, xdata=%f, ydata=%f' %
          (event.button, event.x, event.y, event.xdata, event.ydata))

    if color=="ro":
        pos.append([event.xdata,event.ydata])
    else:
        neg.append([event.xdata,event.ydata])
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


root = Tk()
root.title("graph regrecion")
# root.minsize(width=1500,height=1000)
# root.maxsize(width=800,height=800)
fig = plt.figure(figsize=(15,10))
ax = fig.add_subplot(1,1,1)
# line,=ax.plot([0,25],[0,25])
fig.canvas.draw()

ax.axis([0,25,0,25])
# sticky=Defines how to expand the widget if the resulting cell is larger than the widget
 # itself. This can be any combination of the constants S, N, E, and W, or NW, NE, SW, and
 # SE.
FIGURE =FigureCanvasTkAgg(fig, master=root)
button1 = Button(root,text="Salir",command=root.quit).grid(row=0,column=4, sticky=E)
button2 = Button(root,text="      ",bg="red",command=change_color_red).grid(row=0,column=0)
button3 = Button(root,text="      ",bg="blue",command=change_color_blue).grid(row=0,column=1)
# button4 = Button(root,text="lineal",command=logistic).grid(row=0,column=2)
button4 = Button(root,text="ir ahi",command=fix).grid(row=0,column=3)
button4 = Button(root,text="      ",bg="green",command=change_color_green).grid(row=0,column=4)
cid = fig.canvas.mpl_connect('button_press_event', onclick)

FIGURE.get_tk_widget().grid(row=1,column=0,columnspan=5)
root.mainloop()
