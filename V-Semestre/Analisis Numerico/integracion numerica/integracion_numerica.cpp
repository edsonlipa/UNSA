#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
#define Npartes 10
typedef long double number;

number f1(number x) {
  return pow(x,2);
}
number f2(number x) {
  return exp((2*x)+1)*atan(x+1);
}
number integracion(number a , number b,number (*f)(number) ) {
  number part=(b-a)/Npartes;
  number ans=0;
  for (number i = a+(part/2); i < b; i+=part) {
    // std::cout << " "<<f(i)<< " " << '\n';
    // std::cout << " "<<f(i)*part<< " " << '\n';
    ans+=f(i)*part;
  }
  std::cout << "answer "<< ans<< '\n';
  return ans;
}
number integracion_trapecio(number a , number b,number (*f)(number) ) {
  number part=(b-a)/Npartes;
  number ans=0;
  for (number i = a; i < b; i+=part) {
    // std::cout << " "<<f(i)<< " " << '\n';
    // std::cout << " "<<f(i)*part<< " " << '\n';
    ans+=(f(i)+f(i+part))*part/2;
  }
  std::cout << "answer "<< ans<< '\n';
  return ans;
}
number regla_simpson_simple(number a , number b,number (*f)(number) ) {
  number part=(b-a)/Npartes;
  number ans=0;
  for (number i = a; i < b; i+=(2*part)) {

  ans+=(f(i)+(4*f(i+part)+f(i+(2*part))));
  std::cout << "part:"<<i << '\n';
  }
  std::cout << "answer "<< ans*(part/3)<< '\n';
  return ans;
}
number regla_simpson_compuesta(number a , number b,number (*f)(number) ) {
//
  number part=(b-a)/Npartes;
  number ans=0;
  for (number i = a; i < b; i+=(part*2)) {
    ans+=(f(i)+(4*f(i-part)+f(part*2)));
  }
  std::cout << "answer "<< ans*(part*2/3)<< '\n';
  return (ans*part*2)/3;
}
// void llenararchivo(number final)
// {
  // std::fstream fs;
  // fs.open ("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  //
 // 	ofstream archivo("interpolacionN.csv"|);
// 	for (number i = inicio; i < final; i+=0.5)
// 	{
// 		archivo<<i<<" "<<evaluar_funcion(fun,i)<<endl;
// 		// cout<<i<<" "<<evaluar_funcion(fun,i)<<endl;
// 	}
// 	archivo.close();
// }
int main(int argc, char const *argv[]) {
  // integracion(0,1,f1);
  integracion_trapecio(0,2,f2);
  // regla_simpson_simple(0,2,f2);
  // regla_simpson_compuesta(0,1,f1);

  return 0;
}
