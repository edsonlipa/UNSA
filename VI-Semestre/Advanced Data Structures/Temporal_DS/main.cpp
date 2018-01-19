#include <iostream>
#include "node.h"
#include "temporal_ds.h"

using namespace std;

int main()
{

    Temporal_DS<int> arbol;
//    cout<<" puntero rot "<<(arbol.hash[0]?"si":"no") <<endl;
    cout<<" agregado "<<(arbol.add(5)?"si":"no") <<endl;
    arbol.print_three(2);
    cout<<" agregado 2 :"<<(arbol.add2(6)?"si":"no") <<endl;
    arbol.print_three(2);

//    cout<<" time "<<arbol.time <<endl;
//    Node<int> nuevo(5);
//    Node<int> nuevo1(6);
//    nuevo.sons[0]=&nuevo1;
//    Node<int> nuevo2=nuevo;
//    cout<<"nuevo2 "<<nuevo2.data<<endl;
//    cout<<"nuevo2 puntero hijo "<<(nuevo2.sons[0]?"si":"no") <<endl;

    return 0;
}
