#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:

public:

    struct mod{
        int time;
        unsigned son:1;
        Node<T> * to_node;
        mod(int time,unsigned pos,Node<T> * nuevo):time(time),son(pos),to_node(nuevo){}
        mod():time(0),son(0),to_node(nullptr){}
        };

    T data;
    Node<T> * sons[2];
    mod log;
    Node<T> * back_ptr;
    Node<T>(const Node<T>& copyNode) : data(copyNode.data),back_ptr(copyNode.back_ptr) {sons[0]=copyNode.sons[0];sons[1]=copyNode.sons[1];}

    Node<T>& operator=(const Node<T>&);
    Node<T>(const T& data):data(data),back_ptr(nullptr){sons[0]=nullptr;sons[1]=nullptr;}

};

#endif // NODE_H
