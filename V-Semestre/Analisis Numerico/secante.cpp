#include <iostream>
#include <cmath>

using namespace std;
typedef float number;
number f(number x)
{
  // return exp(-pow(x,2))-x;
  // return pow(x,3)+2*pow(x,2)+10*x-20;
  // return (pow(x,3)*tan(x+2*M_PI))-pow(x,2)+2;
  // return pow(x,5)-(pow(x,3)*10/9)+(x*5/21);
  // return pow(x,3)-3*x+2;
  return -x*atan(x+M_PI)+x*exp(-3*pow(x,2)+1);
}
number update_X(number x_ant,number x,number (*fx)(number))
{
  return x-(fx(x)*(x_ant-x)/(fx(x_ant)-fx(x)));
}
number secante(number r_ant, number r,number (*fx)(number),number tolerancia)
{
  //number r=0;
  std::cout <<r_ant<<"\t"<<r<<"\t"<<f(r)<< '\n';

  while (abs(r-r_ant)>tolerancia) {
    number temp=r;
    r=update_X(r_ant,r,fx);
    r_ant=temp;
  std::cout <<r_ant<<"\t"<<r<<"\t"<<f(r)<< '\n';
  }
  return r;
}


int main() {
  number (*func)(number);
  func=f;

  std::cout << "/* respuesta secante */"<<secante(1.2,1,func,pow(10,-6))<< '\n';
  // std::cout << "/* respuesta falsa pocicion */"<<falsa_posicion(1,2,func,pow(10,-5))<< '\n';
  std::cout << "/* message */"<<f(1) << '\n';
  return 0;
}
