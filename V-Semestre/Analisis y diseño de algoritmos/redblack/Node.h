#ifndef Node_H
#define Node_H
using namespace std;

template<class T>
class NodoRB
{
    public:
        NodoRB(T d)
        {
            dato=d;

            hijos[0]=hijos[1]=0;
            m_color=1;
            m_size=0;
        }
        NodoRB(T d,T d2)
        {
            dato=d;
            dato2=d2;
            hijos[0]=hijos[1]=0;
            m_color=1;
            m_size=0;
        }

        ~NodoRB(){}
        T dato;
        T dato2;
        NodoRB<T>* hijos[2];
        bool m_color;
        int m_size;
        void killme();
};

 template<class T>
 void NodoRB<T>::killme()
 {
    if(hijos[0])hijos[0]->killme();
    if(hijos[1])hijos[1]->killme();
    delete this;
 }



#endif // Node_H
