#include <QCoreApplication>
#include"RB_Tree.h"

int main(int argc, char *argv[])
{

    RedBlack<int> m;
    for(int i=0;i<100;i++)
    {
        m.Add(i);
    }

    m.imprimir();

}


















































//m.Add(20);
//m.Add(18);
//m.Add(12);
//m.Add(13);
//m.Add(21);
//m.Add(48);
//m.Add(37);
//m.Add(103);
//m.Add(57);
//m.Add(23);
//m.Add(49);
//m.Add(36);
//m.Add(1);
