#ifndef L_Range_T_H
#define L_Range_T_H

#include <iostream>
#include "node.h"
#include <vector>

using namespace std;

template<class T>
class L_Range_T
{
public:
    // vector<Node_y<T>> ys;
    Node_x<T>* root;
    L_Range_T();
    Node_x<T> * Build(vector<point<T> *> &in_xs,vector<Node_y<T> > &in_ys);
    void Build_2D_RT(vector<point<T> *> &in_xs,vector<point<T> *> &in_ys);
    void find_S(Node_x<T> **&p,Node_x<T> * &r,int x1,int x2);
    void findx(Node_x<T> * &r,int x,bool r_l,int idx,int y1,int y2);
    void answer(Node_x<T> * &r,int indx ,int y1,int y2);
    Node_x<T> * FindSplitN(int x1,int x2);
    void Query(int,int,int,int);
    void p_r(Node_x<T>* r);
    void print();
};

template<class T>
L_Range_T<T>::L_Range_T()
{
  root=nullptr;
}


template<class T>
void L_Range_T<T>::find_S(Node_x<T> **&p,Node_x<T> * &r,int x1,int x2){
  std::cout<< (r->value<x1) << " //" <<(r->value<x2)<< '\n';
  p=&r;
  if (r->value<=x1==r->value<=x2) {
    p=&r->sons[r->value<x2];
    find_S(p,r->sons[r->value<=x2], x1, x2);
  }
  return;

}
template<class T>
Node_x<T> * L_Range_T<T>::FindSplitN(int x1,int x2){
  Node_x<T> **p;
  find_S(p,this->root, x1, x2);
  return *p;
}

template<class T>
void L_Range_T<T>::answer(Node_x<T> * &r,int indx ,int y1,int y2){
  if (r) {

      std::cout << "bien" << '\n';
      if (r->ys.size()==1) {
        std::cout << "answer "<<r->value<<" "<<r->ys[0].value << '\n';
        return;
      }
      if (r->ys[indx].index[0]>y1&&r->ys[indx].index[0]>y2) answer(r->sons[0],indx,y1,y2);
        /* code */
      if (r->ys[indx].index[1]>y1&&r->ys[indx].index[0]>y2) answer(r->sons[1],indx,y1,y2);

    }
    return;

}

template<class T>
void L_Range_T<T>::findx(Node_x<T> * &r,int x,bool r_l,int idx,int y1,int y2){
    if (r) {
      answer(r->sons[r_l],r->ys[idx].index[r_l],y1,y2);
      // std::cout <<"Node "<<r->value<< " idex " <<r->ys[idx].index[r_l]<< '\n';
      findx(r->sons[r->value<x],x,r_l,r->ys[idx].index[r_l],y1,y2);
    }
    return;

}

template<class T>
void L_Range_T<T>::Query(int x1,int x2,int y1 ,int y2){
    Node_x<T> *SN=FindSplitN(x1,x2);
    std::cout << "SN "<<SN->value << '\n';
    int pos1= 0;
    int index_r= SN->ys.size()-1;
    unsigned m;
    while (pos1<=index_r) {
       m=((index_r+pos1)/2);
      if (y1<SN->ys[m].value) index_r=m-1;
      else pos1=m+1;
    }
    std::cout << y1 << " binari search "<< index_r<< '\n';
    findx(SN->sons[0],x1,true,SN->ys[index_r].index[0],y1,y2);
    std::cout << "bien" << '\n';

    findx(SN->sons[1],x1,false,SN->ys[index_r].index[1],y1,y2);

}

template<class T>
void L_Range_T<T>::print(){

    std::cout << "root " <<this->root->value<< '\n';

    p_r(this->root);

}

template<class T>
void L_Range_T<T>::p_r(Node_x<T> * r){

    if(!r) {/*std::cout << "no existe hijo" << '\n';*/return;}
    cout<<" <-- "<<r->value<<" --> ";
    for (size_t i = 0; i < r->ys.size(); i++) {
      std::cout << "["<< r->ys[i].value <<"]" ;
      std::cout << "{"<<r->ys[i].index[0]<< "}"<< "{"<<r->ys[i].index[1]<< "}" ;

    }
    std::cout << '\n';
    p_r(r->sons[0]);
    p_r(r->sons[1]);
}

template<class T>
Node_x<T> * L_Range_T<T>::Build(vector<point<T> *> &in_xs,vector<Node_y<T> > &in_ys)
{

    if(in_xs.size()==1) {
    // cout<<"Nueva Hoja                                          "<<in_xs[0]->first<<endl;
    Node_x<T>* leaf=new Node_x<T>(in_xs[0]->first);
    leaf->ys=in_ys;
    return leaf;}
    unsigned v;
    if (!in_xs.size()%2)   v = (in_xs.size()/2)-1;
    else{
      if (in_xs.size()==2)    v = 0;
      else                    v = (in_xs.size()/2);

    }
        vector<point<T> *> xl(in_xs.begin(),in_xs.begin()+v+1);
        vector<point<T> *> xr(in_xs.begin()+v+1,in_xs.end());
        vector<Node_y<T>>yl;
        vector<Node_y<T>>yr;
        Node_x<T>* temp=new Node_x<T>(in_xs[v]->first);
// /*commend*/         std::cout << "Nodo "<< in_xs[v]->first<< '\n';

        // cout<<endl;
        int l=0;
        int r=0;
        for(unsigned i = 0;i<in_ys.size();i++){
// /*commend*/           std::cout << " "<<in_ys[i].value<< " " ;
          Node_y<T> nuevo_y =Node_y<T>(in_ys[i].value);
          nuevo_y.pointer=in_ys[i].pointer;
          l<v+1?in_ys[i].index[0]=l:in_ys[i].index[0]=-1;
          r<(in_ys.size()-v-1)?in_ys[i].index[1]=r:in_ys[i].index[1]=-1;
          if(in_ys[i].pointer->first<=in_xs[v]->first){
// /*commend*/             std::cout << "["<< in_ys[i].index[0] <<"]["<< in_ys[i].index[1] <<"]" ;

            yl.push_back(nuevo_y);
            l++;
          }else{
// /*commend*/            std::cout << "["<< in_ys[i].index[0] <<"]["<< in_ys[i].index[1] <<"]" ;

            yr.push_back(nuevo_y);
            r++;
          }
        }
// /*commend*/        cout<<endl;

        temp->ys=in_ys;

        temp->sons[0]=Build(xl,yl);
        temp->sons[1]=Build(xr,yr);
        return temp;
}


template<class T>
void L_Range_T<T>::Build_2D_RT(vector<point<T> *> &in_xs,vector<point<T> *> &in_ys){
    std::vector<Node_y<T>> init_y;
    for(unsigned i=0;i<in_ys.size();i++) {
        Node_y<T> temp_y=Node_y<T>(in_ys[i]->first);
        temp_y.pointer=in_ys[i]->pointer;
        init_y.push_back(temp_y);}

        int v = (in_xs.size()/2)-1;
        vector<point<T> *> xl(in_xs.begin(),in_xs.begin()+v+1);
        vector<point<T> *> xr(in_xs.begin()+v+1,in_xs.end());
        vector<Node_y<T>>yl;
        vector<Node_y<T>>yr;
        this->root  =  new Node_x<T>(in_xs[v]->first);

        int l=0;
        int r=0;
        for(unsigned i = 0;i<init_y.size();i++){
          Node_y<T> nuevo_y =Node_y<T>(init_y[i]);
          l<v+1?init_y[i].index[0]=l:init_y[i].index[0]=-1;
          r<(in_ys.size()-v-1)?init_y[i].index[1]=r:init_y[i].index[1]=-1;
          if(init_y[i].pointer->first<=in_xs[v]->first){
            yl.push_back(nuevo_y);
            l++;
          }else{
            yr.push_back(nuevo_y);
            r++;
          }
        }

        this->root->ys=init_y;
        // cout<<"hijo 0"<<endl;
        this->root->sons[0]=Build(xl,yl);
        // cout<<"hijo 1"<<endl;
        this->root->sons[1]=Build(xr,yr);

}

#endif // L_Range_T_H
