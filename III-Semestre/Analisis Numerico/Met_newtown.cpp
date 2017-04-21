#include <iostream>
#include <cmath>

using namespace std;
typedef float number;
number f1(number x)
{
return x-exp(cos(5*x-1))*atan(pow(x,3)+2*x-4);
}

number df1(number x)
{
  return 5*exp(cos(5*x-1))*atan(pow(x,3)+2*x-4)*sin(5*x-1)-((exp(cos(5*x-1))*pow(x,3)+2)/(pow(pow(x,3)+2*x-4,2)+1))+1;
}

number df_aprox(number (*func)(number),number x,number h)
{
  return (func(x+h)-func(x-h))/(2*h);
}
number newton_dev_aprox(number r0,number (*func)(number),number tolerancia)
{
  std::cout <<"\tr:\t" <<"  f(r):\t"<< '\n';
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
  std::cout <<"\tr:\t" <<"  f(r):\t"<< '\n';
  int cont=0;
  while (abs(func(r0)) > tolerancia&&cont<10) {
    r0=r0-(func(r0)/dfunc(r0));
    std::cout <<cont <<"\t"<< r0 <<"\t"<<func(r0)<< '\n';
    cont++;
  }
  return r0;
}


int main() {
  number (*func)(number)=f1;
  number (*dfunc)(number)=df1;
  number punto=-2;
  number uno=newton(punto,f1,df1,0.0000001);
  number dos=newton_dev_aprox(punto,f1,0.0000001);
  std::cout<<"newton_dev exacta en "<<punto<<" : "<< uno << '\n';
  std::cout<<"newton_dev_aprox en "<<punto<<" : "<< dos << '\n';
  return 0;
}
