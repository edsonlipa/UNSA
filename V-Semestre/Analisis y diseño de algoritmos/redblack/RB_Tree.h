#ifndef RB_TREE_H
#define RB_TREE_H
#include "Node.h"
#include <iostream>
using namespace std;
template<class T>
class RedBlack
{
    public:
        NodoRB<T>* root;
        NodoRB<T>* padre(T d);
        NodoRB<T>* abuelo(T d);
        NodoRB<T>* tio(T d);

        RedBlack()
        {
            root=0;
        }
        ~RedBlack(){if(root)root->killme();}
        bool find_( T d,NodoRB<T>**&p);
        void rotacion_simple(NodoRB<T>* &p, bool c);
        void rotacion_doble(NodoRB<T>* &p, bool c);
        void caso1(NodoRB<T>* &p);
        void caso2(NodoRB<T>* &p);
        void caso3(NodoRB<T>* &p);
        void caso4(NodoRB<T>* &p);
        void caso5(NodoRB<T>* &p);
        void Add(T d);
        void Add(T d,T d2);
        void print(NodoRB<T> *p);
        void imprimir();


};

template<class T>
NodoRB<T>* RedBlack<T>::padre(T d)
{
  NodoRB<T>* father;
  NodoRB<T>* tmp=root;
  if(!root) return 0;
  if(root->dato==d) return 0;
  while(tmp)
  {
    if(tmp->dato==d)return father;
    {
        father=tmp;
        tmp=tmp->hijos[tmp->dato < d];
    }
  }
  return 0;

}

template<class T>
NodoRB<T>* RedBlack<T>::abuelo(T d)
{
    if(padre(d)!=0)

        return padre(padre(d)->dato);
    else
        return 0;
}

template<class T>
NodoRB<T>* RedBlack<T>::tio(T d)
{
  NodoRB<T>* abuel=abuelo(d);
    if(abuel!=0)
    {
        if(padre(d)==abuel->hijos[0] && abuel->hijos[1]!=0)
            return abuel->hijos[1];
        else
        {
            if(padre(d)==abuel->hijos[1] && abuel->hijos[0]!=0)
                return abuel->hijos[0];
            else
                return 0;
        }

    }
    return 0;

}


///izquierda-derecha=true
///derecha-izquierda=false
template<class T>
void RedBlack<T>::rotacion_doble(NodoRB<T>* &p, bool c)
{

    NodoRB<T>* q=p->hijos[!c];
    NodoRB<T>* r=q->hijos[c];
    //-----aumento para tamanios
    int s=0;
    if(r->hijos[c]){ p->m_size=p->m_size-q->m_size+r->hijos[c]->m_size; s=s+p->m_size;}
    else{ p->m_size=p->m_size-q->m_size;s=s+p->m_size;}
    if(r->hijos[!c]){q->m_size=q->m_size-r->m_size+r->hijos[!c]->m_size;s=s+q->m_size;}
    else{ q->m_size=q->m_size-r->m_size;s=s+q->m_size;}
     r->m_size=s+1;
    //---hasta aqi

    p->hijos[!c]=r->hijos[c];
    q->hijos[c]=r->hijos[!c];
    r->hijos[!c]=q;
    r->hijos[c]=p;
    p=r;

}

template<class T>
void RedBlack<T>::rotacion_simple(NodoRB<T>* &p, bool c)
{
    if(c==true){
    NodoRB<T>* q=p->hijos[1];

    if(q->hijos[0]){
    p->m_size=p->m_size-q->m_size +q->hijos[0]->m_size ;
    q->m_size=q->m_size -q->hijos[0]->m_size+p->m_size;}
    else{
        p->m_size=p->m_size-q->m_size  ;
        q->m_size=q->m_size +p->m_size;
    }

    p->hijos[1]=q->hijos[0];
    q->hijos[0]=p;
    p=q;
    }


    if(c==false){
    NodoRB<T>* q=p->hijos[0];
    if(q->hijos[1]){
    p->m_size=p->m_size-p->hijos[0]->m_size +q->hijos[1]->m_size;
    q->m_size=q->m_size -q->hijos[1]->m_size+p->m_size;}
    else{
        p->m_size=p->m_size-p->hijos[0]->m_size ;
        q->m_size=q->m_size +p->m_size;
    }

    p->hijos[0]=q->hijos[1];
    q->hijos[1]=p;
    p=q;
    }
}

template<class T>
void RedBlack<T>::caso5(NodoRB<T>* &p)
{
   // cout<<"caso 5"<<endl;
    NodoRB<T>* father=padre(p->dato);
    NodoRB<T>* Gfather=abuelo(p->dato);
    //cout<<"abuelito"<<Gfather->dato<<endl;
    NodoRB<T>* Gfather_padre=padre(Gfather->dato);
    //cout<<Gfather_padre->dato<<endl;
    if(Gfather->hijos[0]==father && father->hijos[0]==p)
    {
        father->m_color=0;
        Gfather->m_color=1;
        //cout<<"Gfather->padre"<<Gfather_padre->dato<<endl;
        rotacion_simple(Gfather,false);
        if(!Gfather_padre)root=father;
        else
            Gfather_padre->hijos[Gfather_padre->dato < Gfather->dato]=father;

    }
    else
    {
        if(Gfather->hijos[1]==father && father->hijos[1]==p)
        {
           // cout<<"papap"<<father->dato<<endl;
            father->m_color=0;
            Gfather->m_color=1;
            //cout<<"Gfather->padre"<<Gfather_padre->dato<<endl;
            rotacion_simple(Gfather,true);
            if(!Gfather_padre)root=father;
            else
                Gfather_padre->hijos[Gfather_padre->dato < Gfather->dato]=father;
        }
    }
}



template<class T>
void RedBlack<T>::caso4(NodoRB<T>* &p)
{
    //cout<<"caso 4"<<endl;
    //cout<<"p al inicio"<<p->dato<<endl;
    NodoRB<T>* Gfather=abuelo(p->dato);
    NodoRB<T>* father=padre(p->dato);
    NodoRB<T>* Gfather_papa=padre(Gfather->dato);
    if(Gfather->hijos[0]==father && father->hijos[1]==p)
    {
        Gfather->m_color=1;
        p->m_color=0;
        rotacion_doble(Gfather,true);
        //cout<<p->dato<<"p"<<endl;
       // cout<<Gfather->dato<<"Gfather->dato"<<endl;
        if(!Gfather_papa)
            root=Gfather;
        else
        {
            Gfather_papa->hijos[Gfather_papa->dato < Gfather->dato]=Gfather;
        }


    }

    else
    {
        if(Gfather->hijos[1]==father && father->hijos[0]==p)
        {

            Gfather->m_color=1;
            p->m_color=0;
            rotacion_doble(Gfather,false);
            if(!Gfather_papa)
            root=Gfather;
            else
            {
                Gfather_papa->hijos[Gfather_papa->dato<Gfather->dato]=Gfather;
            }
        }
        else
            //cout<<"caso 5"<<endl;
            caso5(p);
    }


}


template<class T>
void RedBlack<T>::caso3(NodoRB<T>* &p)
{

   if(tio(p->dato))
   {
        if(tio(p->dato)->m_color==1 && padre(p->dato)->m_color==1)
        {
            padre(p->dato)->m_color=0;
            tio(p->dato)->m_color=0;
            NodoRB<T>* abuelo_=abuelo(p->dato);
            abuelo_->m_color=1;
            caso1(abuelo_);
        }
        else
            caso4(p);

   }
   else
        caso4(p);

}

template<class T>
void RedBlack<T>::caso2(NodoRB<T>* &p)
{

    NodoRB<T>* father=padre(p->dato);

    if(father->m_color==0) return ;
    else
        caso3(p);

}

template<class T>
void RedBlack<T>::caso1(NodoRB<T>* &p)
{

    if(root==p)
        p->m_color=0;
    else
        caso2(p);
}


template<class T>
bool RedBlack<T>::find_(T d,NodoRB<T>**&p)
{
    p=&root;
    while(*p)
    {
        if((*p)->dato==d)
            return true;
        p=&((*p)->hijos[(*p)->dato < d]);
    }
    return false;
}

template<class T>
void RedBlack<T>::Add(T d)
{
    NodoRB<T>** p;
    if(find_(d,p))return;
    else
    {
        if(!root) root=new NodoRB<T>(d);
        *p=new NodoRB<T>(d);
        caso1(*p);

    }
}

template<class T>
void RedBlack<T>::Add(T d,T d2)
{
    NodoRB<T>** p;
    if(find_(d,p))return;
    else
    {
        if(!root) root=new NodoRB<T>(d,d2);
        *p=new NodoRB<T>(d,d2);
        caso1(*p);

    }
}


template<class T>
void RedBlack<T>::print(NodoRB<T> *p)
{
    if(!p)return;

    print(p->hijos[0]);
    cout<<p->dato<<endl;
    print(p->hijos[1]);
}

template<class T>
void RedBlack<T>::imprimir()
{

    print(root);

}
#endif // RB_TREE_H
