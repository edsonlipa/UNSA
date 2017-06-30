#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <fstream>
#include "DescomposicionPLU.h"
using namespace std;
typedef vector<vector<numero (*)(numero,numero,numero)>> function_aprox_matrix;
typedef vector<vector<numero (*)(numero,numero,numero)>> function_matrix;
typedef vector<numero (*)(numero,numero,numero)>function_matrixcolumn;
typedef vector<numero (*)(numero,numero,numero)>function_row;

numero f1(numero x,numero y,numero z)
{
    return pow(x,2)+pow(y,2)+pow(z,2)-1;
}
numero f2(numero x,numero y,numero z)
{
    return -pow(x,2)-pow(y,2)+pow(z,2);
}
numero f3(numero x,numero y,numero z)
{
    return x-(3*y)+z;
}
///------------------------------funciones para derivada norma;
numero derivf_1x(numero x,numero y,numero z)
{
    return 2*x;
}

numero derivf_1y(numero x,numero y,numero z)
{
    return 2*y;
}
numero derivf_1z(numero x,numero y,numero z)
{
    return 2*z;
}

numero derivf_2x(numero x, numero y,numero z)
{
    return -2*x;
}

numero derivf_2y(numero x,numero y,numero z)
{
    return 2*y;
}
numero derivf_2z(numero x,numero y,numero z)
{
    return -2*z;
}
numero derivf_3x(numero x, numero y,numero z)
{
    return 1;
}

numero derivf_3y(numero x,numero y,numero z)
{
    return -3;
}
numero derivf_3z(numero x,numero y,numero z)
{
    return 1;
}
///--------------------------------------funciones para la derivada aproximada-----------
// numero derivaproxf_1x(numero x,numero y,numero h)
// {
//     return (f1(x+h,y)-f1(x,y))/h;
// }
//
// numero derivaproxf_1y(numero x,numero y,numero h)
// {
//     return (f1(x,y+h)-f1(x,y))/h;
// }
//
// numero derivaproxf_2x(numero x, numero y,numero h)
// {
//     return (f2(x+h,y)-f2(x,y))/h;
// }
//
// numero derivaproxf_2y(numero x,numero y,numero h)
// {
//     return (f2(x,y+h)-f2(x,y))/h;
// }

numero ErrorAbsoluto(colmnMatrix b, colmnMatrix a)
{
    numero aux=0;
    for(unsigned int i=0; i<a.size(); i++)
    {
        aux=aux+pow(a[i]-b[i],2);
    }

    return pow(aux,0.5);

}
matrix evaluateMjacob (function_matrix JF,colmnMatrix p_act)
{   matrix a(p_act.size(),row(p_act.size()));
    for(unsigned i=0; i<a.size(); i++)
    {
        for(unsigned j=0; j<a.size(); j++)
        {

            a[i][j]=JF[i][j](p_act[0],p_act[1],p_act[2]);
        }
    }
    return a;

}
// matrix evaluateMjacob_aprox (function_aprox_matrix JF,colmnMatrix p_act,numero h)
// {   matrix a(p_act.size(),row(p_act.size()));
//     for(unsigned i=0; i<a.size(); i++)
//     {
//         for(unsigned j=0; j<a.size(); j++)
//         {
//
//             a[i][j]=JF[i][j](p_act[0],p_act[1],h);
//         }
//     }
//     return a;
//
// }
colmnMatrix evaluateColmFunc(function_matrixcolumn funcion,colmnMatrix p_act)
{
    colmnMatrix a(p_act.size());
    for(unsigned int i=0; i<a.size(); i++)
    {
        a[i]=funcion[i](p_act[0],p_act[1],p_act[2]);
    }
    return a;
}
void negative(colmnMatrix &a)
{
    for(unsigned int i=0; i<a.size(); i++)
    {
        a[i]=-1*a[i];
    }
}
colmnMatrix sumBetweenMcolmn(colmnMatrix a,colmnMatrix b)
{
    colmnMatrix c(a.size());
    for (int i=0; i<a.size(); i++)
    {
        c[i]=a[i]+b[i];
    }
    return c;
}

void newtonRapshon(function_matrixcolumn F,function_matrix JF,colmnMatrix &p_act,int iteraciones)
{
    ofstream archivo("newtonRapshon.csv");
    matrix Jacob(3,vector<numero>(3));
    colmnMatrix Fun(3);
    colmnMatrix Aux(3);
    colmnMatrix p_ant(3);
    int iteration=1;
    archivo<<"iteracion"<<"\t"<<"Valor x"<<"\t"<<"Valor x"<<endl;

    do{
              p_ant=p_act;
        Jacob=evaluateMjacob(JF,p_act);
        std::cout<<'\n' << "/* jacobino */" << '\n';
        print(Jacob);
        Fun=evaluateColmFunc(F,p_act);
        std::cout<<'\n' << "/* F */" << '\n';
        print(Fun);
        negative(Fun);

        Aux=resolver_conPLU(Jacob,Fun);
        std::cout<<'\n' << "/* resolucion */" << '\n';
        print(Aux);
        p_act=sumBetweenMcolmn(p_act,Aux);

        cout<<iteration<<" "<<p_act[0]<<" "<<p_act[1]<<" "<<p_act[1]<<endl;
        archivo<<iteration<<"\t"<<p_act[0]<<"\t"<<p_act[1]<<endl;
        iteration++;

   }while(ErrorAbsoluto(p_ant,p_act)>pow(10,-2) && iteration<=iteraciones);

}

// void newtonRapshon(function_matrixcolumn F,function_aprox_matrix JF,colmnMatrix &p_act,int iteraciones,numero h)
// {
//
//     ofstream archivo("newtonRapshon_derivAprox.csv");
//     matrix Jacob(3,vector<numero>(3));
//     colmnMatrix Fun(3);
//     colmnMatrix Aux(3);
//     colmnMatrix p_ant(3);
//     int iteration=1;
//     archivo<<"iteracion"<<"\t"<<"Valor x"<<"\t"<<"Valor x"<<endl;
//     do{
//         p_ant=p_act;
//         Jacob=evaluateMjacob_aprox(JF,p_act,h);
//         Fun=evaluateColmFunc(F,p_act);
//         negative(Fun);
//         print(Jacob);
//         Aux=resolver_conPLU(Jacob,Fun);
//         p_act=sumBetweenMcolmn(p_act,Aux);
//
//         cout<<iteration<<" "<<p_act[0]<<" "<<p_act[1]<<""<<endl;
//         archivo<<iteration<<"\t"<<p_act[0]<<"\t"<<p_act[1]<<endl;
//
//         iteration++;
//
//    }while(ErrorAbsoluto(p_ant,p_act)>0.0000001 && iteration<=iteraciones);
//
// }


int main()
{
    colmnMatrix p_act {1,2,2};
    cout<<"-----newton Rapshon con derivada exacta------"<<endl;
    function_matrixcolumn F {f1,f2};
    function_matrix JF {{derivf_1x,derivf_1y,derivf_1z},{derivf_2x,derivf_2y,derivf_2z},{derivf_3x,derivf_3y,derivf_3z}};
    newtonRapshon(F,JF,p_act,100);
    // cout<<"-----newton Rapshon con derivada aproximada------"<<endl;
    // function_aprox_matrix JFA {derivaproxf_1x,derivaproxf_1y},{derivaproxf_2x,derivaproxf_2y}};
    // numero h=0.0001;
    // newtonRapshon(F,JFA,p_act,2,h);



    return 0;
}
