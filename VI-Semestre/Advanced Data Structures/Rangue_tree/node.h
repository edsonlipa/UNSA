#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
using namespace std;

template<class T>
struct point {
    T first;
    point * pointer;
    point(T i,point * p){first=i;pointer=p;}
};
///------------------------------node to tree------------------------

template <class T>
class Node_y
{
public:

    T value;
    point<T> * pointer;
    int index[2];
    Node_y(const T& val):value(val){}
//    Node_y(const Node_y<T>& copy):value(copy.val),pointer(copy.pointer){}
    Node_y(const point<T>& copy):value(copy.first),pointer(copy.pointer){}

};

template <class T>
class Node_x
{

public:

    T value;
    Node_x<T> * sons[2];
    vector<Node_y<T>> ys;
    Node_x<T>( T data):value(data){sons[0]=nullptr;sons[1]=nullptr;}

};


#endif // NODE_H
