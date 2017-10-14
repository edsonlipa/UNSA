#include <iostream>
#include "node.h"


using namespace std;

int main()
{
    Node<int> nuevo(5);

    Node<int> nuevo1(6);
//    nuevo.sons[0]=&nuevo1;
    Node<int> nuevo2=nuevo;
    cout<<"nuevo2 "<<nuevo2.data<<endl;
    cout<<"nuevo2 puntero hijo "<<(nuevo2.sons[0]?"si":"no") <<endl;

    return 0;
}
