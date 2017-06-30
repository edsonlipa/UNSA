#include <iostream>
#include <cmath>
#include <unistd.h>
using namespace std;
typedef float number;
number f(number x)
{
  // return pow(x,7)+pow(x,5)-pow(x,2)+1;
  // return (pow(x,3)*tan(x+2*M_PI))-pow(x,2)+2;
  // return (pow(x,3)*tan(x+2*M_PI))-pow(x,2)+2;
  // return pow(x,5)-((10/9)*pow(x,3))+(x*(5/21));
  return -x*atan(x+M_PI)+x*exp(-3*pow(x,2)+1);
}

number biseccion(number a, number b,number (*func)(number),number tolerancia)
{
  number r=0;
  std::cout <<"  a:\t"<<"  b:\t"<< "  r:\t"<< r <<"  f(r):\t"<< '\n';

  while (b-a>tolerancia) {
    // std::cout << "entra al wailr" << '\n';
    r=(a+b)/2;
    if((func(a)*func(r))>0){
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
  std::cout <<"  r:\t"<<"  a:\t"<<"  b:\t"<<  r <<"  f(r):\t"<< '\n';
  std::cout <<a<< " /* message */ "<<b  << '\n';
  while (b-a>tolerancia) {
   r=a-((func(a)*(b-a))/(func(b)-func(a)));
    if((func(a)*func(r))<0){
        b=r;
    }else{
        a=r;
    }
    std::cout << r <<"\t"<< a<<"\t"<<b<< "\t"<<func(r)<< '\n';
    // sleep(1);
}
  return r;
}


int main() {
  number (*func)(number);
  func=f;
  std::cout << "/* respuesta biseccion */"<<biseccion(0,1,func,pow(10,-6))<< '\n';
  std::cout << "/* respuesta falsa pocicion */"<<falsa_posicion(0.2,0.7,func,pow(10,-5))<< '\n';
  return 0;
}
