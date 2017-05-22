#include <iostream>
#include <cmath>

using namespace std;
typedef double number;
number f1(number x)
{
  // return (exp(-x))-(log(x)/2)-(0.2);  return -x*atan(x+M_PI)+x*exp(-3*pow(x,2)+1);
  return -x*atan(x+M_PI)+x*exp(-3*pow(x,2)+1);

}

number df1(number x)
{
  // return 5*exp(cos(5*x-1))*atan(pow(x,3)+2*x-4)*sin(5*x-1)-((exp(cos(5*x-1))*pow(x,3)+2)/(pow(pow(x,3)+2*x-4,2)+1))+1;
  // return (-(exp(-x)))-(1/(2*x));
  return -6*exp(1-3*pow(x,2))*pow(x,2)-exp(1-3*pow(x,2))-(x/(pow(x+M_PI,2)+1))-atan(x+M_PI);
}

number df_aprox(number (*func)(number),number x,number h)
{
  return (func(x+h)-func(x-h))/(2*h);
}
number newton_dev_aprox(number r0,number (*func)(number),number tolerancia)
{
  std::cout <<"\tr:\t" <<"  df(r):\t"<<"  f(r):\t"<< '\n';
  int cont=0;

  number (*df)(number)=func;
  while (abs(func(r0)) > tolerancia&&cont<10000) {
    r0=r0-(func(r0)/df_aprox(df,r0,0.001));
    std::cout <<cont <<"\t"<< r0 <<"\t"<<func(r0)<< '\n';
    cont++;
  }
  return r0;
}
number newton(number r0,number (*func)(number),number (*dfunc)(number),number tolerancia)
{
  std::cout <<"\tr:\t" <<"  df(r):\t"<<"  f(r):\t"<< '\n';

  int cont=0;
  std::cout <<cont <<"\t"<< r0 <<"\t"<<dfunc(r0)<<"\t"<<func(r0)<< '\n';

  while (abs(func(r0)) > tolerancia&&cont<100) {
    r0=r0-(func(r0)/dfunc(r0));
    std::cout <<cont <<"\t"<< r0 <<"\t"<<dfunc(r0)<<"\t"<<func(r0)<<"\t"<< func(r0)/dfunc(r0)<< '\n';
    cont++;
  }
  return r0;
}

int main() {
  number (*func)(number)=f1;
  number (*dfunc)(number)=df1;
  number punto=1.5;
  number uno=newton(punto,func,dfunc,0.000000001);
  // number dos=newton_dev_aprox(punto,f1,0.0000001);
  std::cout<<"newton_dev exacta en "<<punto<<" : "<< uno << '\n';
  // std::cout <<'\n';
  // std::cout<<"newton_dev_aprox en "<<punto<<" : "<< dos << '\n';
  return 0;
}
