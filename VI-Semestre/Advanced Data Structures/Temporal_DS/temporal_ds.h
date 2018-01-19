#ifndef TEMPORAL_DS_H
#define TEMPORAL_DS_H
#include <iostream>
#include "node.h"
#include <vector>

using namespace std;
template<class T>
class Temporal_DS
{
public:
    unsigned time=0;
    Node<T> * hash[20]={0};
    Temporal_DS();
    bool add(T data);
    bool add2(T data);
    bool add_T(T data);
    bool find(int time,T val,Node<T> **& seeker);
    bool find_T(T val,Node<T> **& seeker);
    Node<T> * romper(Node<T> * copy,Node<T> * nuevo);
    void print_three(int time);
    void print(Node<T>* r);
};

template<class T>
Temporal_DS<T>::Temporal_DS()
{
    cout<<"******************arbol iniciado********************"<<endl;
//    this->time=0;
//    this->hash[0]=0;
}
template<class T>
Node<T> * Temporal_DS<T>::romper(Node<T> * src,Node<T> * nuevo)
{
    Node<T>* copia=new Node<T>;
    copia=src;
    copia->sons[src->mod.son]=src->mod.to_node;
    copia->sons[!src->mod.son]=src->mod.to_node;
    if(copia->back_ptr){
        hash[time]=copia;
    }
    else if(copia->back_ptr->mod.to_node){
        romper(copia->back_ptr,copia);
    }else{
        copia->back_ptr->mod.time=time;
        copia->back_ptr->mod.to_node=copia;
        copia->back_ptr->mod.son=(copia->data>copia->back_ptr->data);
    }


    return copia;
}

template<class T>
void Temporal_DS<T>::print_three(int time)
{
    while (!hash[time]) {
        time--;
    }
    print(hash[time]);

}

template<class T>
void Temporal_DS<T>::print(Node<T>* r)
{
    if(!r)return;

    print(r->sons[0]);
    cout <<" "<<r->data<<" "<<endl;
    print(r->sons[1]);

}

template<class T>
bool Temporal_DS<T>::add(T data)
{
    cout<<"nuevo nodo"<<endl;
    if(!this->hash[0]){this->time++;this->hash[0]=new Node<T>(data);return true;}
    return false;
}

template<class T>
bool Temporal_DS<T>::add_T(T data)
{
    if(!this->hash[0]){this->time++;this->hash[0]=new Node<T>(data);return true;}
    else{
        Node<T>**temp=new Node<T> *;
        if(!find(time,data,temp)){
            *temp=new Node<T>(data);
            this->time++;
            return true;
        }
        return false;
    }

}

template<class T>
bool Temporal_DS<T>:: find_T(T val,Node<T> **& seeker)
{
    while (!hash[time]) {
        time--;
    }
    seeker=&(hash[time]);
    while(*seeker){
        if((*seeker)->data==val){
            return true;
        }

        if((*seeker)->sons[!(*seeker)->data<val] ){ //si existen hijos
            if((*seeker)->mod.to_node){
                if((*seeker)->mod.son==((*seeker)->data<val)){
                    (seeker)=&((*seeker)->mod.to_node);
                }else {
                    (seeker)=&((*seeker)->sons[!(*seeker)->data<val]);
                }
            }
            else{

                (seeker)=&((*seeker)->sons[!(*seeker)->data<val]);
            }
        }
        else if((*seeker)->mod.to_node){// si existe modificacion
            if((*seeker)->mod.son==((*seeker)->data<val)){
                (seeker)=&((*seeker)->mod.to_node);

            }
            else {
                /*mandar romper*/
                Node<T>* nuevo_hijo=new Node<T>;
                Node<T>* nuevo_nodo=new Node<T>;
                nuevo_nodo=romper((*seeker),nuevo_hijo)
                (seeker)=&(nuevo_nodo->sons[!(*seeker)->data<val]);
//                romper=true;/*actulizar puntero a hijo lejitimo de duplicado*/
            }
        }
        else{
            (seeker)=&((*seeker)->mod.to_node);
            (*seeker)->mod.time=time;
            (*seeker)->mod.son=(*seeker)->data<val;
//            (seeker)=&((*seeker)->sons[!(*seeker)->data<val]);
        }
    }
//    cout<<"buscando... "<<(*seeker)->data<<endl;
    return false;
}

template<class T>
bool Temporal_DS<T>::add2(T data)
{
    Node<T>**temp=new Node<T> *;
    if(!find(time,data,temp)){

        *temp=new Node<T>(data);
        this->time++;
        return true;
    }
    return false;
}

template<class T>
bool Temporal_DS<T>:: find(int time ,T val,Node<T> **& seeker)
{
    while (!hash[time]) {
        time--;
    }
    seeker=&(hash[time]);
    while(*seeker){
        if((*seeker)->data==val){
            return true;
        }
   //     (*seeker)=(*seeker)->data<val?(*seeker)->sons[0]:(*seeker)->sons[1];
        (seeker)=&((*seeker)->sons[!(*seeker)->data<val]);
    }
//    cout<<"buscando... "<<(*seeker)->data<<endl;
    return false;
}

#endif // TEMPORAL_DS_H
