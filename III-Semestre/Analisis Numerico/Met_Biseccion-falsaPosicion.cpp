#include <iostream>
#include <math.h>

using namespace std;
typedef float number;
number f(number x)
{
  // return pow(x,7)+pow(x,5)-pow(x,2)+1;
  // return (pow(x,3)*tan(x+2*M_PI))-pow(x,2)+2;
  return (pow(x,3)*tan(x+2*M_PI))-pow(x,2)+2;
}

number biseccion(number a, number b,number (*func)(number),number tolerancia)
{
  number r=0;
  std::cout <<"  a:\t"<<"  b:\t"<< "  r:\t"<< r <<"  f(r):\t"<< '\n';

  while (b-a>tolerancia) {
   r=(a+b)/2;
    if((func(a)*func(r))<0){
        b=r;
    }else{
        a=r;
    }
  std::cout <<a<<"\t"<<b<< "\t"<< r <<"\t"<<func(r)<< '\n';
}
  return r;
}

number falsa_posicion(number a, number b,number (*func)(number),number tolerancia)
{
  number r=0;
  std::cout <<"  a:\t"<<"  b:\t"<< "  r:\t"<< r <<"  f(r):\t"<< '\n';

  while (b-a>tolerancia) {
   r=(a-func(a)*(b-a))/(func(a)-func(b));
    if((func(a)*func(r))<0){
        b=r;
    }else{
        a=r;
    }
    std::cout <<a<<"\t"<<b<< "\t"<< r <<"\t"<<func(r)<< '\n';
}
  return r;
}


int main() {
  number (*func)(number);
  func=f;
  std::cout << "/* respuesta biseccion */"<<biseccion(3,4,func,pow(10,-5))<< '\n';
  // std::cout << "/* respuesta falsa pocicion */"<<falsa_posicion(1,2,func,pow(10,-5))<< '\n';
  return 0;
}
